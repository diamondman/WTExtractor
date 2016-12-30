#!/usr/bin/python3
import datetime
import sys
import struct
import collections
import uuid
import sys

class WTFormatException(Exception):
    pass

def rev_offset(num, offset):
    tmp = num-offset
    return 0x100-tmp if tmp < 0 else tmp

def str_decode(s):
    return s.decode()

def UTC_decode(s):
    i = int_decode(s)
    return datetime.datetime.fromtimestamp(i) if i else None

def int_decode(s):
    return struct.unpack("<L", s)[0]

def BDY_decode(s):
    return s[-5:].decode()

def UUID_decode(s):
    pt0 = s[:4][::-1]
    pt1 = s[4:6][::-1]
    pt2 = s[6:8][::-1]
    pt3 = s[8:]
    return uuid.UUID(bytes=pt0+pt1+pt2+pt3)

class WTDecoder(object):
    field_interpretation = [
        (0, str_decode, "Copyright"),
        (4, UTC_decode, "CreatedDate"),
        (4, UTC_decode, "StartValidDate"),
        (4, UTC_decode, "ExpireDate"),
        (16, UUID_decode, "WTVerUUID"),
        (16, UUID_decode, "ResourceUUID"),
        (4, str_decode, "License"),
        (0, BDY_decode, "BodyMarker"),
        (4, int_decode, "EncodeType"),
    ]

    def __init__(self, f):
        self._index = 0
        self._last_crypt_byte = 0
        self._f = f
        self._decoded = False
        self.magic = None
        self.urls = None
        self.rawfields = None
        self.fields = None
        self.comment = None
        self.created = None
        self.base_type = None
        self.outdata = None

    def _read(self, *args, **kwargs):
        return self._f.read(*args, **kwargs)

    def _readline(self, *args, **kwargs):
        return self._f.readline(*args, **kwargs)

    def _readb(self):
        return self._read(1)[0]

    def _readintcrypt(self, table):
        return int_decode(bytes((self.decodeByte(table) for i in range(4))))

    def _read_str_crypt(self, table, cnt):
        return bytes((self.decodeByte(table) for i in range(cnt))).decode()

    def decodeByte(self, table, inbyte=None):
        if inbyte is None:
            inbyte = self._readb()
        res = inbyte ^ self._last_crypt_byte ^\
              table[self._index%len(table)]
        self._index += 1
        self._last_crypt_byte = inbyte
        return res

    def decode_payload(self, enc_key_table):
        self.outdata = bytearray((
            self.decodeByte(enc_key_table, inbyte) for inbyte in self._read()))

    def _decode_urls(self):
        if self.fields.get("EncodeType", 0) < 300:
            return

        media_enc_table = self.calc_enc_key_table_TYPEMEDIA()
        self.urls = {}
        while True:
            urltype = self.decodeByte(media_enc_table)
            url_len = self._readintcrypt(media_enc_table)
            always300_0 = self._readintcrypt(media_enc_table)
            always300_1 = self._readintcrypt(media_enc_table)
            if url_len == 0 and urltype == 0:
                break

            urlbody = self._read_str_crypt(media_enc_table, url_len)
            self.urls.setdefault(urltype, []).append(urlbody)

    def decode(self):
        self._decoded = True
        self.magic = self._read(4)
        if self.magic != b"WLD3":
            raise WTFormatException("File does not have correct Magic. Exiting.", -1)

        headline = self._readline().decode()
        self.base_type, magic_msg = headline.split(' ', 1)
        if magic_msg != "WildTangent 3D 300 Compressed and Patented\r\n":
            raise WTFormatException("File does not have correct Magic Line. Exiting.", -2)

        if self._read(20) != b'Converted by XtoWT: ':
            raise WTFormatException(
                "File does not have correct Magic 2nd Line. Exiting.", -3)

        self.created = datetime.datetime.strptime(
            self._readline().strip().decode(), '%a %b %d %H:%M:%S %Y')

        if self._readline() != b'\r\n':
            raise WTFormatException(
                "File Should have an empty line after date. Exiting.", -4)

        self.comment = self._readline().decode().strip()

        if self._readline().strip() != b'.START':
            raise WTFormatException("File missing .START section. Exiting.", -5)

        fieldcount = rev_offset(ord(self._read(1)), 0xC5)
        if fieldcount != 9:
            raise WTFormatException(
                "Only know how to use files with 9 headers, not %s. Exiting."%fieldcount, -6)
        fieldlens = [rev_offset(ord(self._read(1)), 0x39 + (13*i)) for i in range(fieldcount)]
        self.rawfields = [self._read(fieldlen) for fieldlen in fieldlens]

        self._process_fields()

        self._decode_urls()

        self.decode_payload(self.calc_enc_key_table_TYPEDATA())

        return self.outdata

    def _process_fields(self):
        self.fields = collections.OrderedDict()
        for i, rawfield in enumerate(self.rawfields):
            size, func, name = WTDecoder.field_interpretation[i]
            self.fields[name] = func(rawfield[:size] if size else rawfield)

    def calc_hash_byte_TYPEDATA(self):
        max_field_len = max((len(f) for f in self.rawfields))
        enc_byte = 0
        for i, data in enumerate(self.rawfields):
            if max_field_len > 0:
                for j in range(max_field_len):
                    c = data[j % len(data)] if len(data) >= 1 else 0
                    enc_byte ^= i + j + c * (j + 1)
        return enc_byte & 0xFF

    def calc_enc_key_table_TYPEDATA(self, enc_byte=None):
        if enc_byte is None:
            enc_byte = self.calc_hash_byte_TYPEDATA()
        enc_key_table = [enc_byte] * max((len(f) for f in self.rawfields))
        for i in range(len(enc_key_table)):
            key = enc_key_table[i]
            chr_index = i + 7
            for field in self.rawfields:
                key ^= field[chr_index % len(field)]\
                       if ( len(field) >= 1 ) else 0
                chr_index += 13
            enc_key_table[i] = key & 0xFF
        return enc_key_table

    def calc_enc_key_table_TYPEMEDIA(self, enc_byte=None):
        if enc_byte is None:
            enc_byte = self.calc_hash_byte_TYPEDATA()
        enc_key_table = [enc_byte] * max((len(f) for f in self.rawfields))

        for i in range(len(enc_key_table)):
            key = enc_key_table[i]
            for j, field in enumerate(self.rawfields):
                key ^= field[(j + i) % len(field)]\
                       if ( len(field) >= 1 ) else 0
            enc_key_table[i] = key & 0xFF
        return enc_key_table

    def __repr__(self):
        return "%s(Decoded: %s; type: %s)"%\
            (type(self).__name__, self._decoded, self.base_type)

    def __str__(self):
        if not self._decoded:
            return repr(self)
        s = []
        s.append("FTYPE:    %s" % decoder.base_type)
        s.append("CREATED:  %s" % decoder.created)
        s.append("COMMENT:  %s" % decoder.comment)
        s.append("FieldCnt: %s" % len(decoder.fields))
        max_name_len = max((len(fi[2]) for fi in WTDecoder.field_interpretation))
        for k, v in decoder.fields.items():
            s.append(("  {:<%s}: {}" % max_name_len).format(k,v))

        if decoder.urls:
            s.append("URLS:")
            for k,v in decoder.urls.items():
                s.append("  TYPE %s" % k)
                for url in v:
                    s.append("    %s" % url)

        return "\n".join(s)

if __name__ == "__main__":
    import os
    import argparse
    #import pyunpack

    parser = argparse.ArgumentParser(
        description='Decrypt WildTangent WebDriver Compressed Files.')
    parser.add_argument('inpath', type=str, help='File Path of Compressed file')
    parser.add_argument('outpath', type=str, default=None, nargs='?',
                        help='Filepath to put output. Defaults to stdout.')
    parser.add_argument('-q', dest='quiet', action="store_true",
                        help='Supress file information output.')

    args = parser.parse_args()

    inpath = os.path.expanduser(args.inpath)
    try:
        with open(inpath, "rb") as f:
            decoder = WTDecoder(f)
            decoded_data = decoder.decode()
    except WTFormatException as e:
        msg, code = e.args
        print(msg, file=sys.stderr)
        sys.exit(code)

    ############### DRAWING OUTPUT ###############
    if not args.quiet:
        print(decoder, file=sys.stderr)

    if args.outpath is None:
        sys.stdout.buffer.write(decoded_data)
    else:
        with open(os.path.expanduser(args.outpath), 'wb') as fout:
            fout.write(decoded_data)

    if not args.quiet:
        print("File Successfully written.", file=sys.stderr)

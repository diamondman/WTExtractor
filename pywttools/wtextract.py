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

    file_type_info = {
        "png": (1, 'png'),
        "jpg": (1, 'jpg'),
        "wav": (1, 'wav'),
        "mid": (1, 'mid'),
        "rmi": (1, 'rmi'),
        "wt":  (0, 'pwt'),
        "cfg": (2, 'cfg'),
        "dat": (2, 'dat'),
        "ini": (2, 'ini'),
        "txt": (2, 'txt'),
        "cab": (1, 'cab'),
        "tmp": (1, 'tmp'),
    }

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
        self.out_ext = None
        self.outdata = None
        self.containscab = False

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
        decoded_data = bytearray((self.decodeByte(enc_key_table, inbyte)
                             for inbyte in self._read()))
        self.containscab = decoded_data[:4] == b'MSCF'

        if self.containscab:
            import patoolib
            import tempfile

            tmpoutdir = tempfile.TemporaryDirectory()
            tmpcabf = tempfile.NamedTemporaryFile()
            tmpcabf.write(decoded_data)
            tmpcabf.flush()

            try:
                patoolib.extract_archive(
                    tmpcabf.name, outdir=tmpoutdir.name,
                verbosity=-1)

                file_list = os.listdir(tmpoutdir.name)
                if len(file_list) is 0:
                    raise WTFormatException(
                        "Extracted cab file contains no files!")
                if len(file_list) > 1:
                    raise WTFormatException(
                        "Extracted cab file contained multiple "
                        "files %s" % file_list)
                with open(os.path.join(tmpoutdir.name, file_list[0]),
                          'rb') as f:
                    decoded_data = f.read()

            except patoolib.util.PatoolError as e:
                print("Failed to extract cab file, contents may have "
                      "started with CAB file magic number, or be "
                      "corrupt. Emitting the contents. Error: <%s>" % e)

        self.outdata = decoded_data

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
        if self._decoded:
            raise Exception("Already decoded")
        self._decoded = True
        self.magic = self._read(4)
        if self.magic != b"WLD3":
            raise WTFormatException("File does not have correct Magic. Exiting.", -1)

        headline = self._readline().decode()
        self.base_type, magic_msg = headline[1:].split(' ', 1)
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

        self.comment = ""
        while True:
            s = self._readline().decode()
            if s == ".START\n":
                break
            self.comment += s

        fieldcount = rev_offset(ord(self._read(1)), 0xC5)
        if fieldcount != 8 and fieldcount != 9:
            raise WTFormatException(
                "WT archives must have either 8 or 9 headers, not %s. Exiting."%fieldcount, -6)
        fieldlens = [rev_offset(ord(self._read(1)), 0x39 + (13*i)) for i in range(fieldcount)]
        self.rawfields = [self._read(fieldlen) for fieldlen in fieldlens]

        self._process_fields()

        self._decode_urls()

        type_, self.out_ext = WTDecoder.file_type_info.get(
            self.base_type, (None, None))
        if type_ == 0:
            table = self.calc_enc_key_table_TYPEMODEL()
        elif type_ == 1:
            table = self.calc_enc_key_table_TYPEMEDIA()
        elif type_ == 2:
            table = self.calc_enc_key_table_TYPEDATA()
        else:
            raise Exception("No known way to extract type '%s'"%self.base_type)

        self.decode_payload(table)

        return self.outdata

    def _process_fields(self):
        self.fields = collections.OrderedDict()
        for i, rawfield in enumerate(self.rawfields):
            size, func, name = WTDecoder.field_interpretation[i]
            self.fields[name] = func(rawfield[:size] if size else rawfield)

        #Write fake version header for v 1.0 format
        if len(self.rawfields) == 8:
            _, _, name = WTDecoder.field_interpretation[8]
            self.fields[name] = 100


    ########### HASH BYTE CALCULATION
    def calc_hash_byte_TYPEMEDIADATA(self):
        max_field_len = max((len(f) for f in self.rawfields))
        enc_byte = 0
        for i, data in enumerate(self.rawfields):
            if max_field_len > 0:
                for j in range(max_field_len):
                    c = data[j % len(data)] if len(data) >= 1 else 0
                    enc_byte ^= i + j + c * (j + 1)
        return enc_byte & 0xFF

    def calc_hash_byte_TYPEMODEL(self):
        max_field_len = max((len(f) for f in self.rawfields))
        enc_byte = 0
        for data in self.rawfields:
            if max_field_len > 0:
                for j in range(max_field_len):
                    c = data[j % len(data)] if len(data) >= 1 else 0
                    enc_byte ^= c
        return enc_byte & 0xFF

    ########### HASH TABLE CALCULATION
    def calc_enc_key_table_TYPEDATA(self, enc_byte=None):
        if enc_byte is None:
            enc_byte = self.calc_hash_byte_TYPEMEDIADATA()
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
            enc_byte = self.calc_hash_byte_TYPEMEDIADATA()

        enc_key_table = [enc_byte] * max((len(f) for f in self.rawfields))

        for i in range(len(enc_key_table)):
            key = enc_key_table[i]
            for j, field in enumerate(self.rawfields):
                key ^= field[(j + i) % len(field)]\
                       if ( len(field) >= 1 ) else 0
            enc_key_table[i] = key & 0xFF
        return enc_key_table

    def calc_enc_key_table_TYPEMODEL(self, enc_byte=None):
        if enc_byte is None:
            enc_byte = self.calc_hash_byte_TYPEMODEL()
        enc_key_table = [enc_byte] * max((len(f) for f in self.rawfields))

        for i in range(len(enc_key_table)):
            key = enc_key_table[i]
            for j, field in enumerate(self.rawfields):
                key ^= field[i % len(field)]\
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
        s.append("OUTEXT    %s" % decoder.out_ext)
        s.append("CREATED:  %s" % decoder.created)
        s.append("COMMENT:  %s" % decoder.comment)
        s.append("Metadata Headers:")
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

    parser = argparse.ArgumentParser(
        description='Decrypt WildTangent WebDriver Compressed Files.')
    parser.add_argument('inpath', type=str, help='File Path of Compressed file')
    parser.add_argument('outpath', type=str, default=None, nargs='?',
                        help='Filepath to put output. Defaults to stdout. A - will output a new file in the same directory.')
    parser.add_argument('-q', dest='quiet', action="store_true",
                        help='Supress file information output.')
    parser.add_argument('-s', dest='stay', action="store_true",
                        help='Waits for enter after extract.')

    args = parser.parse_args()

    inpath = os.path.expanduser(args.inpath)
    try:
        with open(inpath, "rb") as f:
            decoder = WTDecoder(f)
            decoded_data = decoder.decode()
    except WTFormatException as e:
        msg, code = e.args
        print(msg, file=sys.stderr)
        if args.stay:
            input()
        sys.exit(code)

    if not args.quiet:
        print(decoder, file=sys.stderr)

    if args.outpath is None:
        sys.stdout.buffer.write(decoded_data)
    else:
        outpath = os.path.expanduser(
            os.path.splitext(inpath)[0]+"."+decoder.out_ext\
            if args.outpath == '-' else args.outpath)

        if outpath == inpath:
            basepath = outpath
            i = 0
            while outpath == inpath:
                outpath = basepath + "_" + str(i)
                i += 1
        print("Writing to", repr(outpath), file=sys.stderr)
        with open(outpath, 'wb') as fout:
            fout.write(decoded_data)

    if not args.quiet:
        print("File Successfully written.", file=sys.stderr)

    if args.stay:
        input()

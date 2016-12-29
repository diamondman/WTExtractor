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
    return datetime.datetime.fromtimestamp(int_decode(s))

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

field_interpretation = [
    (0, str_decode, "Copyright"),
    (4, UTC_decode, "CreatedDate"),
    (4, int_decode, "field_44"),
    (4, int_decode, "field_48"),
    (16, UUID_decode, "WTVerUUID"),
    (16, UUID_decode, "ResourceUUID"),
    (4, str_decode, "License"),
    (0, BDY_decode, "BodyMarker"),
    (4, int_decode, "EncodeType"),
]

def decompress_payload(enc_data, enc_key_table, starti=0, subkey=0):
    outdata = bytearray(len(enc_data))
    for i, inbyte in enumerate(enc_data):
        outdata[i] = inbyte ^ subkey ^\
                     enc_key_table[(i+starti)%len(enc_key_table)]
        subkey = inbyte
    return outdata

def process_fields(rawfields):
    fields = collections.OrderedDict()
    for i, rawfield in enumerate(rawfields):
        size, func, name = field_interpretation[i]
        fields[name] = func(rawfield[:size] if size else rawfield)
    return fields

class Decoder(object):
    def __init__(self, f):
        self._index = 0
        self._last_crypt_byte = 0
        self._f = f

    def decode(self, table):
        inbyte = self._f.read(1)[0]
        res = inbyte ^ self._last_crypt_byte ^\
              table[self._index%len(table)]
        self._index += 1
        self._last_crypt_byte = inbyte
        return res

    def decode_urls(self, rawfields):
        media_enc_table = calc_enc_key_table_TYPEMEDIA(rawfields)

        urls = {}

        while True:
            urltype = self.decode(media_enc_table)
            url_len = int_decode(bytes((self.decode(media_enc_table) for i in range(4))))
            always300_0 = int_decode(bytes((self.decode(media_enc_table)
                                            for i in range(4))))
            always300_1 = int_decode(bytes((self.decode(media_enc_table)
                                            for i in range(4))))
            if url_len == 0 and urltype == 0:
                break

            urlbody = bytes((self.decode(media_enc_table)
                             for i in range(url_len))).decode()
            urls.setdefault(urltype, []).append(urlbody)

        return urls

def calc_hash_byte_TYPEDATA(rawfields):
    max_field_len = max((len(f) for f in rawfields))
    enc_byte = 0
    for i, data in enumerate(rawfields):
        if max_field_len > 0:
            for j in range(max_field_len):
                c = data[j % len(data)] if len(data) >= 1 else 0
                enc_byte ^= i + j + c * (j + 1)
    return enc_byte & 0xFF

def calc_enc_key_table_TYPEDATA(rawfields, enc_byte=None):
    if enc_byte is None:
        enc_byte = calc_hash_byte_TYPEDATA(rawfields)
    enc_key_table = [enc_byte] * max((len(f) for f in rawfields))
    for i in range(len(enc_key_table)):
        key = enc_key_table[i]
        chr_index = i + 7
        for field in rawfields:
            key ^= field[chr_index % len(field)]\
                   if ( len(field) >= 1 ) else 0
            chr_index += 13
        enc_key_table[i] = key & 0xFF
    return enc_key_table

def calc_enc_key_table_TYPEMEDIA(rawfields, enc_byte=None):
    if enc_byte is None:
        enc_byte = calc_hash_byte_TYPEDATA(rawfields)
    enc_key_table = [enc_byte] * max((len(f) for f in rawfields))

    for i in range(len(enc_key_table)):
        key = enc_key_table[i]
        for j, field in enumerate(rawfields):
            key ^= field[(j + i) % len(field)]\
                   if ( len(field) >= 1 ) else 0
        enc_key_table[i] = key & 0xFF
    return enc_key_table

def main(f, showdetails=False):
    magic = f.read(4)
    if magic != b"WLD3":
        raise WTFormatException("File does not have correct Magic. Exiting.", -1)

    headline = f.readline().decode()
    base_type, magic_msg = headline.split(' ', 1)
    if magic_msg != "WildTangent 3D 300 Compressed and Patented\r\n":
        raise WTFormatException("File does not have correct Magic Line. Exiting.", -2)

    if f.read(20) != b'Converted by XtoWT: ':
        raise WTFormatException(
            "File does not have correct Magic 2nd Line. Exiting.", -3)

    datestr = f.readline().strip().decode()
    header_createdate = datetime.datetime.strptime(datestr, '%a %b %d %H:%M:%S %Y')

    if f.readline() != b'\r\n':
        raise WTFormatException(
            "File Should have an empty line after date. Exiting.", -4)

    commentfield = f.readline().decode().strip()

    if f.readline().strip() != b'.START':
        raise WTFormatException("File missing .START section. Exiting.", -5)

    fieldcount = rev_offset(ord(f.read(1)), 0xC5)
    if fieldcount != 9:
        raise WTFormatException(
            "Only know how to use files with 9 headers, not %s. Exiting."%fieldcount, -6)
    fieldlens = [rev_offset(ord(f.read(1)), 0x39 + (13*i)) for i in range(fieldcount)]
    rawfields = [f.read(fieldlen) for fieldlen in fieldlens]

    fields = process_fields(rawfields)

    decoder = Decoder(f)

    urls = decoder.decode_urls(rawfields) if fields.get("EncodeType", 0)>=300 else {}

    enc_key_table = calc_enc_key_table_TYPEDATA(rawfields)

    outdata = decompress_payload(f.read(), enc_key_table,
                                 decoder._index, decoder._last_crypt_byte)

    ############### DRAWING OUTPUT ###############
    if showdetails:
        print("FTYPE:    %s" % base_type, file=sys.stderr)
        print("CREATED:  %s" % header_createdate, file=sys.stderr)
        print("COMMENT:  %s" % commentfield, file=sys.stderr)
        print("FieldCnt: %s" % fieldcount, file=sys.stderr)
        max_name_len = max((len(fi[2]) for fi in field_interpretation))
        for k, v in fields.items():
            print(("  {:<%s}: {}" % max_name_len).format(k,repr(v)),
                  file=sys.stderr)

        if urls:
            print("URLS:", file=sys.stderr)
            for k,v in urls.items():
                print("  TYPE %s" % k, file=sys.stderr)
                for url in v:
                    print("    %s" % url, file=sys.stderr)

    return outdata

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
            unencoded_data = main(f, showdetails=not args.quiet)
    except WTFormatException as e:
        msg, code = e.args
        print(msg, file=sys.stderr)
        sys.exit(code)

    if args.outpath is None:
        sys.stdout.buffer.write(unencoded_data)
    else:
        with open(os.path.expanduser(args.outpath), 'wb') as fout:
            fout.write(unencoded_data)

    if not args.quiet:
        print("File Successfully written.", file=sys.stderr)

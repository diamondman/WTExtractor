import datetime
import sys
import struct
import collections
import uuid
import sys

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

def main(inpath, outpath, showdetails=False):
    inpath = os.path.expanduser(inpath)
    f = open(inpath, "rb")
    magic = f.read(4)
    if magic != b"WLD3":
        print("File does not have correct Magic. Exiting.", file=sys.stderr)
        sys.exit(-1)

    headline = f.readline().decode()
    base_type, magic_msg = headline.split(' ', 1)
    if magic_msg != "WildTangent 3D 300 Compressed and Patented\r\n":
        print("File does not have correct Magic Line. Exiting.", file=sys.stderr)
        sys.exit(-2)

    if f.read(20) != b'Converted by XtoWT: ':
        print("File does not have correct Magic 2nd Line. Exiting.", file=sys.stderr)
        sys.exit(-3)

    datestr = f.readline().strip().decode()
    datetime_object = datetime.datetime.strptime(datestr, '%a %b %d %H:%M:%S %Y')

    emptyline = f.readline()
    if emptyline != b'\r\n':
        print("File Should have an empty line after date. Exiting.", file=sys.stderr)
        sys.exit(-4)

    commentfield = f.readline().decode().strip()

    if f.readline().strip() != b'.START':
        print("File missing .START section. Exiting.", file=sys.stderr)
        sys.exit(-5)

    fieldcount = rev_offset(ord(f.read(1)), 0xC5)
    if fieldcount != 9:
        print("Only know how to use files with 9 headers, not %s. Exiting."%fieldcount,
              file=sys.stderr)
        sys.exit(-6)
    fieldlens = [rev_offset(ord(f.read(1)), 0x39 + (13*i)) for i in range(fieldcount)]
    rawfields = [f.read(fieldlen) for fieldlen in fieldlens]

    fields = collections.OrderedDict()
    for i, rawfield in enumerate(rawfields):
        size, func, name = field_interpretation[i]
        fields[name] = func(rawfield[:size] if size else rawfield)

    max_field_len = max(fieldlens)
    enc_byte = 0
    for i, rawfield in enumerate(rawfields):
        if max_field_len > 0:
            for j in range(max_field_len):
                buff_len = len(rawfield)
                if buff_len >= 1:
                    c = rawfield[j % buff_len]
                else:
                    c = 0
                enc_byte ^=  i + j + c * (j + 1)
    enc_byte &= 0xFF

    enc_key_table = [enc_byte]*max_field_len
    for i in range(max_field_len):
        key = enc_key_table[i]

        chr_index = i + 7
        for field_i, field_val in enumerate(rawfields):
            if ( len(field_val) >= 1 ):
                element = field_val[chr_index % len(field_val)];
            else:
                element = 0;
            key ^= element;
            chr_index += 13;

        enc_key_table[i] = key & 0xFF


    enc_data = f.read()

    outdata = bytearray(len(enc_data))
    subkey = 0
    for i, inbyte in enumerate(enc_data):
        outdata[i] = inbyte ^ subkey ^ enc_key_table[i%max_field_len]
        subkey = inbyte

    f.close()

    ############### DRAWING OUTPUT ###############
    if showdetails:
        print("FTYPE:    %s" % base_type, file=sys.stderr)
        print("CREATED:  %s" % datetime_object, file=sys.stderr)
        print("COMMENT:  %s" % commentfield, file=sys.stderr)
        print("FieldCnt: %s" % fieldcount, file=sys.stderr)
        print("MaxFieldLen: %s"%max_field_len, file=sys.stderr)
        #print("ENCKEYT:  %s"%\
        #      (", ".join([hex(a)for a in enc_key_table])), file=sys.stderr)

        max_name_len = max((len(fi[2]) for fi in field_interpretation))
        for k, v in fields.items():
            print(("  {:<%s}: {}" % max_name_len).format(k,repr(v)),
                  file=sys.stderr)

    ############### WRITE FILE ###############
    if outpath is None:
        sys.stdout.buffer.write(outdata)
    else:
        with open(os.path.expanduser(outpath), 'wb') as fout:
            fout.write(outdata)

    if showdetails:
        print("File Successfully written.", file=sys.stderr)

if __name__ == "__main__":
    import os
    import argparse
    import pyunpack

    parser = argparse.ArgumentParser(
        description='Decrypt WildTangent WebDriver Compressed Files.')
    parser.add_argument('inpath', type=str, help='File Path of Compressed file')
    parser.add_argument('outpath', type=str, default=None, nargs='?',
                        help='Filepath to put output. Defaults to stdout.')

    args = parser.parse_args()

    main(args.inpath, args.outpath, showdetails=True)

#!/usr/bin/python3
import math
import struct
import numpy as np
from bitarray import bitarray

class PWTFormatException(Exception):
    pass

class BitfieldReader(object):
    def __init__(self, f):
        self._f = f
        self._bytebit = 0
        self._currbyte = None

    def _consumebytebits(self, count):
        if self._bytebit is 0:
            self._currbyte = self._f.read(1)[0]
            self._bytebit = 0

        if count+self._bytebit > 8:
            raise ValueError('Only works for bits in current byte')
        res = (self._byte >> self._bytebit) & ((1<<count)-1)
        self._bytebit = (self._bytebit + count)%8
        return res

    def _readbyte(self):
        if self._bytebit is 0:
            return self._consumebytebits(8)
        bitsneedednext = self._bytebit
        return self._consumebytebits(self.bytebitsremaining)\
            | (self._consumebytebits(bitsneedednext)\
               << (8-bitsneedednext))

    def _readsubbyte(self, bitcount):
        if bitcount > 8:
            raise ValueError('Only works for bits in current byte')
        left_in_byte = self.bytebitsremaining
        if left_in_byte < bitcount:
            bitsneedednext = bitcount - left_in_byte
            return self._consumebytebits(left_in_byte) |\
                (self._consumebytebits(bitsneedednext) << left_in_byte)
        else:
            return self._consumebytebits(bitcount)

    def readbits(self, bitcount):
        numsout = []
        for _ in range(bitcount//8):
            numsout.append(self._readbyte())

        if bitcount % 8:
            numsout.append(self._readsubbyte(bitcount % 8))

        return bytes(numsout[::-1])

    @property
    def bytebitsremaining(self):
        return 8 - self._bytebit

    @property
    def _byte(self):
        return self._currbyte

class PWTDecode(object):
    def __init__(self, f):
        self._f = f

    def decode(self):
        self.magic = self._read(4)
        if self.magic != b"\x00\x00\x00\x13":
            raise PWTFormatException("File does not have correct Magic. Exiting.", -1)

        self.global_min = struct.unpack('>3f', self._read(12))
        self.global_max = struct.unpack('>3f', self._read(12))
        self.veryclose, self.prettyclose = struct.unpack(
            '>ii', self._read(8))

        self.dowrite_vertices, self.dowrite_normals,\
            self.vertex_bit_num, self.vertex_bit_num_1,\
            self.normal_bit_number, self.f44, self.f48\
            = struct.unpack('>7i', self._read(28))

        self.dowrite_vertices, self.dowrite_normals\
            = bool(self.dowrite_vertices), bool(self.dowrite_normals)

        self.vertex_count, self.normal_count, self.face_count, self.f40\
            = struct.unpack('>3ii', self._read(16))

        #####################################
        self.frame = ModelFrame(self)

        print("\nConsumed Bytes:", f.tell(), hex(f.tell()))

    def _read(self, *args, **kwargs):
        return self._f.read(*args, **kwargs)

    def _readline(self, *args, **kwargs):
        return self._f.readline(*args, **kwargs)

    def __str__(self):
        represent = (
            ("GlobalMin", "global_min"),
            ("GlobalMax", "global_max"),
            ("VeryClose", "veryclose"),
            ("PrettyClose", "prettyclose"),
            ("IncVertices", "dowrite_vertices"),
            ("IncNormals", "dowrite_normals"),
            ("VBitNum", "vertex_bit_num"),
            ("VBitNum1", "vertex_bit_num_1"),
            ("NBitNum", "normal_bit_number"),
            ("f44", "f44"),
            ("f48", "f48"),
            ("VertexCount", "vertex_count"),
            ("NormalCount", "normal_count"),
            ("FaceCount", "face_count"),
            ("f40", "f40"),
            ("Frame", "frame"),
        )

        max_name_len = max((len(fi[0]) for fi in represent))

        s = []
        for name, field in represent:
            value = getattr(self, field)
            if isinstance(value, list):
                s.append(("{:<%s}:" % max_name_len)\
                         .format(name))
                s += ["  "+str(item) for item in value]
            else:
                value = str(value).splitlines()
                if len(value) is 1:
                    s.append(("{:<%s}: {}" % max_name_len)\
                             .format(name, value[0]))
                else:
                    value = tuple(("  "+v for v in value))
                    s.append(("{:<%s}:" % max_name_len)\
                             .format(name))
                    s += value

        return "\n".join(s)

class ModelFrame(object):

    def _read(self, *args, **kwargs):
        return self._pwt._read(*args, **kwargs)

    def __init__(self, pwt):
        self._pwt = pwt

        self.subframe_count, = struct.unpack('>i', self._read(4))

        name_buff = bytearray()
        while True:
            c = self._read(1)[0]
            name_buff.append(c)
            if c == 0:
                break
        self.name = struct.unpack('s', name_buff)[0][:-1].decode('utf8')

        mata = struct.unpack('>4f', self._read(4*4))
        matb = struct.unpack('>4f', self._read(4*4))
        matc = struct.unpack('>4f', self._read(4*4))
        matd = struct.unpack('>4f', self._read(4*4))
        self.matrix = np.matrix([mata, matb, matc, matd])

        self.has_animation = bool(self._read(1)[0])
        self.has_visuals = bool(self._read(1)[0])

        self.animation = None
        if self.has_animation:
            animationsize = struct.unpack('>i', self._read(4))[0]
            D3DOptions = struct.unpack('>i', self._read(4))[0]
            self.animation = []
            for _ in range(animationsize):
                dvTime = struct.unpack('>f', self._read(4))[0]
                keytype = struct.unpack('>i', self._read(4))[0]
                ani_A, ani_B, ani_C, ani_D\
                    = struct.unpack('>4f', self._read(4*4))
                self.animation.append(
                    (dvTime, keytype, ani_A, ani_B, ani_C, ani_D))

            raise NotImplementedError()

        if self.has_visuals:
            self.visuals = ModelVisuals(self)
        else:
            self.visuals = None

    def __str__(self):
        represent = (
            ("SubFrameCount", "subframe_count"),
            ("Name", "name"),
            ("Matrix", "matrix"),
            ("HasAnimation", "has_animation"),
            ("HasVisuals", "has_visuals"),
            ("Animation", "animation"),
            ("Visuals", "visuals"),
        )

        max_name_len = max((len(fi[0]) for fi in represent))

        s = []
        for name, field in represent:
            value = getattr(self, field)
            if isinstance(value, list):
                s.append(("{:<%s}:" % max_name_len)\
                         .format(name))
                s += ["  "+str(item) for item in value]
            else:
                value = str(value).splitlines()
                if len(value) is 1:
                    s.append(("{:<%s}: {}" % max_name_len)\
                             .format(name, value[0]))
                else:
                    value = tuple(("  "+v for v in value))
                    s.append(("{:<%s}:" % max_name_len)\
                             .format(name))
                    s += value

        return "\n".join(s)

class ModelVisuals(object):
    @property
    def _pwt(self):
        return self._frame._pwt

    def _read(self, *args, **kwargs):
        return self._pwt._read(*args, **kwargs)

    def __init__(self, frame):
        self._frame = frame

        self.vcount, self.ncount, self.fcount\
            = struct.unpack('>3i', self._read(12))
        texcount = self._read(1)[0]

        ###### VERTICES ######

        maxbbox_dimen = max((
            self._pwt.global_max[0] - self._pwt.global_min[0],
            self._pwt.global_max[1] - self._pwt.global_min[1],
            self._pwt.global_max[2] - self._pwt.global_min[2],
        ))

        bf = BitfieldReader(self._pwt._f)
        self.vertexcount, = struct.unpack('>i', bf.readbits(32))
        self.normalcount, = struct.unpack('>i', bf.readbits(32))

        if self.vertexcount != self.normalcount:
            print(self.vertexcount, self.normalcount)
            print("FRAME COUNT", self.subframe_count)
            raise Exception("Don't know how to handle "
                            "diff norm vert count")

        self.bboxMIN = struct.unpack('>3f', bf.readbits(3*4*8))

        bbx = struct.unpack('>B', bf.readbits(6))[0]
        bby = struct.unpack('>B', bf.readbits(6))[0]
        bbz = struct.unpack('>B', bf.readbits(6))[0]

        self.vertex_unused_bits = (bbx, bby, bbz)

        scaled_vertices = []
        for _ in range(self.vertexcount):
            x = bf.readbits(self._pwt.vertex_bit_num-bbx)
            x = b'\x00'*(4-len(x)) + x
            y = bf.readbits(self._pwt.vertex_bit_num-bby)
            y = b'\x00'*(4-len(y)) + y
            z = bf.readbits(self._pwt.vertex_bit_num-bbz)
            z = b'\x00'*(4-len(z)) + z

            x = struct.unpack('>i', x)[0]
            y = struct.unpack('>i', y)[0]
            z = struct.unpack('>i', z)[0]

            scaled_vertices.append((x,y,z))

        oddbitnum = (1 << self._pwt.vertex_bit_num) - 1
        self.vertices = [((v[0]*maxbbox_dimen/oddbitnum) + self.bboxMIN[0],
                     (v[1]*maxbbox_dimen/oddbitnum) + self.bboxMIN[1],
                     (v[2]*maxbbox_dimen/oddbitnum) + self.bboxMIN[2])
        for v in scaled_vertices]

        ########## NORMALS ##########
        bf = BitfieldReader(self._pwt._f)

        norm_test1, = struct.unpack('>i', bf.readbits(32))
        norm_test2, = struct.unpack('>i', bf.readbits(32))

        if norm_test1 != norm_test2:
            raise Exception("Don't know how to handle "
                            "diff norm vert count")

        self.norm_bboxMIN = struct.unpack('>3f', bf.readbits(3*4*8))
        #Only needed for non vertices..... or something
        self.norm_bboxMAX = struct.unpack('>3f', bf.readbits(3*4*8))

        norm_bbx = struct.unpack('>B', bf.readbits(6))[0]
        norm_bby = struct.unpack('>B', bf.readbits(6))[0]
        norm_bbz = struct.unpack('>B', bf.readbits(6))[0]

        scaled_normals = []
        for _ in range(self.normalcount):
            x = bf.readbits(self._pwt.normal_bit_number-bbx)
            x = b'\x00'*(4-len(x)) + x
            y = bf.readbits(self._pwt.normal_bit_number-bby)
            y = b'\x00'*(4-len(y)) + y
            z = bf.readbits(self._pwt.normal_bit_number-bbz)
            z = b'\x00'*(4-len(z)) + z

            x = struct.unpack('>i', x)[0]
            y = struct.unpack('>i', y)[0]
            z = struct.unpack('>i', z)[0]
            scaled_normals.append((x,y,z))

        maxbbox_dimen_normals = max((
            self.norm_bboxMAX[0] - self.norm_bboxMIN[0],
            self.norm_bboxMAX[1] - self.norm_bboxMIN[1],
            self.norm_bboxMAX[2] - self.norm_bboxMIN[2],
        ))

        maxnum = (1 << self._pwt.normal_bit_number) - 1
        self.normals = [
            ((v[0]*maxbbox_dimen_normals/maxnum) + self.norm_bboxMIN[0],
             (v[1]*maxbbox_dimen_normals/maxnum) + self.norm_bboxMIN[1],
             (v[2]*maxbbox_dimen_normals/maxnum) + self.norm_bboxMIN[2])
            for v in scaled_normals]

        ############### FACES ###############

        face_vertex_bit_length = math.ceil(math.log2(self.vcount))

        bf = BitfieldReader(self._pwt._f)

        self.faces = []
        for _ in range(self.fcount):
            face_ints = []
            normal_ints = []
            for _ in range(3):
                n = bf.readbits(3)
                n = struct.unpack('>i', b'\x00'*(4-len(n)) + n)[0]
                normal_ints.append(n)

                v = bf.readbits(3)
                v = struct.unpack('>i', b'\x00'*(4-len(v)) + v)[0]
                face_ints.append(v)

            self.faces.append((tuple(face_ints), tuple(normal_ints)))

        ############### TEXMAP ###############

        texmapU = []
        for _ in range(self.vcount):
            texmapU.append(struct.unpack('>i', self._read(4))[0])

        texmapV = []
        for _ in range(self.vcount):
            texmapV.append(struct.unpack('>i', self._read(4))[0])

        ############### FACE DETAIL ###############
        self.face_details = []

        for _ in range(self.fcount):
            texture_name = struct.unpack('>b', self._read(1))[0]
            texture_color = struct.unpack('>I', self._read(4))[0]
            texture_power = struct.unpack('>f', self._read(4))[0]
            emmisivity = struct.unpack('>3f', self._read(12))
            specularity = struct.unpack('>3f', self._read(12))

            face_d = {"texture_name":texture_name,
                      "texture_color":texture_color,
                      "texture_power":texture_power,
                      "emmisivity":emmisivity,
                      "specularity":specularity}
            self.face_details.append(face_d)

    def __str__(self):
        represent = (
            ("Vertexcount", "vertexcount"),
            ("Normalcount", "normalcount"),
            ("bboxMIN", "bboxMIN"),
            ("VertexUnusedBits", "vertex_unused_bits"),
            ("Vertices", "vertices"),
            ("Normals", "normals"),
            ("Faces", "faces"),
            ("FaceDetails", "face_details"),
        )

        max_name_len = max((len(fi[0]) for fi in represent))

        s = []
        for name, field in represent:
            value = getattr(self, field)
            if isinstance(value, list):
                s.append(("{:<%s}:" % max_name_len)\
                         .format(name))
                s += ["  "+str(item) for item in value]
            else:
                value = str(value).splitlines()
                if len(value) is 1:
                    s.append(("{:<%s}: {}" % max_name_len)\
                             .format(name, value[0]))
                else:
                    value = tuple(("  "+v for v in value))
                    s.append(("{:<%s}:" % max_name_len)\
                             .format(name))
                    s += value

        return "\n".join(s)

if __name__ == "__main__":
    import os
    import argparse

    parser = argparse.ArgumentParser(
        description='Decrypt WildTangent WebDriver Model.')
    parser.add_argument('inpath', type=str, help='File Path of pwt file')
    parser.add_argument('outpath', type=str, default=None, nargs='?',
                        help='Filepath to put output. Defaults to stdout. A - will output a new file in the same directory.')
    parser.add_argument('-q', dest='quiet', action="store_true",
                        help='Supress file information output.')
    parser.add_argument('-s', dest='stay', action="store_true",
                        help='Waits for enter after extract.')

    args = parser.parse_args()

    inpath = os.path.expanduser(args.inpath)
    with open(inpath, "rb") as f:
        decoder = PWTDecode(f)
        decoder.decode()
        print(decoder)

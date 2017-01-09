#!/usr/bin/python3
import struct
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

        dowrite_vertices, dowrite_normals, vertex_bit_num, vertex_bit_num_1,\
            normal_bit_number, f44, f48\
            = struct.unpack('>7i', self._read(28))

        self.vertex_count, self.normal_count, self.face_count\
            = struct.unpack('>3i', self._read(12))

        f40, = struct.unpack('>i', self._read(4))
        #####################################

        self.subframe_count, = struct.unpack('>i', self._read(4))

        name_buff = bytearray()
        while True:
            c = self._read(1)[0]
            name_buff.append(c)
            if c == 0:
                break
        self.name = struct.unpack('s', name_buff)[0][:-1].decode('utf8')

        self.matrix = struct.unpack('>16f', self._read(16*4))

        self.has_animation = bool(self._read(1)[0])
        self.has_visuals = bool(self._read(1)[0])

        if self.has_animation:
            raise NotImplementedError()

        if self.has_visuals:
            f_vcount, f_ncount, f_fcount\
                = struct.unpack('>3i', self._read(12))
            texcount = self._read(1)[0]

        ###### VERTICES ######

        maxbbox_dimen = max((
            self.global_max[0] - self.global_min[0],
            self.global_max[1] - self.global_min[1],
            self.global_max[2] - self.global_min[2],
        ))

        bf = BitfieldReader(self._f)
        test1, = struct.unpack('>i', bf.readbits(32))
        test2, = struct.unpack('>i', bf.readbits(32))

        if test1 != test2:
            raise Exception("Don't know how to handle "
                            "diff norm vert count")

        self.bboxMIN = struct.unpack('>3f', bf.readbits(3*4*8))

        bbx = struct.unpack('>B', bf.readbits(6))[0]
        bby = struct.unpack('>B', bf.readbits(6))[0]
        bbz = struct.unpack('>B', bf.readbits(6))[0]

        scaled_vertices = []
        for _ in range(test1):
            x = bf.readbits(vertex_bit_num-bbx)
            x = b'\x00'*(4-len(x)) + x
            y = bf.readbits(vertex_bit_num-bby)
            y = b'\x00'*(4-len(y)) + y
            z = bf.readbits(vertex_bit_num-bbz)
            z = b'\x00'*(4-len(z)) + z

            x = struct.unpack('>i', x)[0]
            y = struct.unpack('>i', y)[0]
            z = struct.unpack('>i', z)[0]

            scaled_vertices.append((x,y,z))

        #scaled_vertices = scaled_vertices[-1:] + scaled_vertices[:-1]

        oddbitnum = (1 << vertex_bit_num) - 1
        vertices = [((v[0]*maxbbox_dimen/oddbitnum) + self.bboxMIN[0],
                     (v[1]*maxbbox_dimen/oddbitnum) + self.bboxMIN[1],
                     (v[2]*maxbbox_dimen/oddbitnum) + self.bboxMIN[2])
        for v in scaled_vertices]

        ########## NORMALS ##########
        bf = BitfieldReader(self._f)

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
        for _ in range(test1):
            x = bf.readbits(normal_bit_number-bbx)
            x = b'\x00'*(4-len(x)) + x
            y = bf.readbits(normal_bit_number-bby)
            y = b'\x00'*(4-len(y)) + y
            z = bf.readbits(normal_bit_number-bbz)
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

        maxnum = (1 << normal_bit_number) - 1
        normals = [
            ((v[0]*maxbbox_dimen_normals/maxnum) + self.norm_bboxMIN[0],
             (v[1]*maxbbox_dimen_normals/maxnum) + self.norm_bboxMIN[1],
             (v[2]*maxbbox_dimen_normals/maxnum) + self.norm_bboxMIN[2])
            for v in scaled_normals]


        print("HEADER")
        print("  GlobalMin:  ", self.global_min)
        print("  GlobalMax:  ", self.global_max)
        print("  VeryClose:  ", self.veryclose)
        print("  PrettyClose:", self.prettyclose)
        print("  IncVertices:", bool(dowrite_vertices))
        print("  IncNormals: ", bool(dowrite_normals))
        print("  VBitNum:    ", vertex_bit_num)
        print("  VBitNum1:   ", vertex_bit_num_1)
        print("  NVitNum:    ", normal_bit_number)
        print("  f44:        ", f44)
        print("  f48:        ", f48)
        print("  VertexCount:", self.vertex_count)
        print("  NormalCount:", self.normal_count)
        print("  FaceCount:  ", self.face_count)
        print("  f40:        ", f40)
        print("SubFrameCount: ", self.subframe_count)
        print("Name:          ", repr(self.name))
        print("Matrix:")
        print("   ", self.matrix[:4])
        print("   ", self.matrix[4:8])
        print("   ", self.matrix[8:12])
        print("   ", self.matrix[12:])
        print("HasAnimation:", self.has_animation)
        print("HasVisuals:", self.has_visuals)
        print("FrameVertexCount:", f_vcount)
        print("FrameNormalCount:", f_ncount)
        print("FrameFaceCount:  ", f_fcount)
        print("TextureCount:    ", texcount)

        print("FrameVertexCount2:", test1)
        print("FrameNormalCount2:", test2)
        print("BBOXMIN:", self.bboxMIN)
        #print("BBOXMAX:", self.bboxMAX)
        print("VTRX_BBX/Y/Z:", bbx, bby, bbz)
        #print("%s vertices X:%s Y:%s Z:%s bits. %s bits total"%
        #      (test1, vertex_bit_num-bbx,
        #       vertex_bit_num-bby, vertex_bit_num-bbz,
        #       (vertex_bit_num*3-bbx-bby-bbz)*test1))
        #print("SCALED(%s)"%len(scaled_vertices), scaled_vertices)
        print("VERTICES:", vertices)

        print()
        print("NormVertexCount2:", norm_test1)
        print("NormNormalCount2:", norm_test2)
        print("NORM_BBOXMIN:", self.norm_bboxMIN)
        print("NORM_BBOXMAX:", self.norm_bboxMAX)
        print("NORM_BBX/Y/Z:", norm_bbx, norm_bby, norm_bby)
        #print("%s normals X:%s Y:%s Z:%s bits. %s bits total"%
        #      (norm_test2, normal_bit_number-norm_bbx,
        #       normal_bit_number-norm_bby, normal_bit_number-norm_bbz,
        #       (normal_bit_number*3-norm_bbx-norm_bby-norm_bbz)*norm_test2))
        #print(scaled_normals)
        print("Normals:", normals)

    def _read(self, *args, **kwargs):
        return self._f.read(*args, **kwargs)

    def _readline(self, *args, **kwargs):
        return self._f.readline(*args, **kwargs)


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

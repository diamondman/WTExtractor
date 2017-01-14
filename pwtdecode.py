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
            self.vertex_bit_accuracy, self.vertex_bit_accuracy_1,\
            self.normal_bit_accuracy, self.f44, self.f48\
            = struct.unpack('>7i', self._read(28))

        self.dowrite_vertices, self.dowrite_normals\
            = bool(self.dowrite_vertices), bool(self.dowrite_normals)

        self.vertex_count, self.normal_count, self.face_count, self.f40\
            = struct.unpack('>3ii', self._read(16))

        #####################################
        self.frame = ModelFrame(self)

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
            ("VAccuracy", "vertex_bit_accuracy"),
            ("VAccuracy1", "vertex_bit_accuracy_1"),
            ("NAccuracy", "normal_bit_accuracy"),
            ("f44", "f44"),
            ("f48", "f48"),
            ("VertexCount", "vertex_count"),
            ("NormalCount", "normal_count"),
            ("FaceCount", "face_count"),
            ("f40", "f40"),
            ("Frame", "frame"),
        )
        return do_str(self, represent)

class ModelFrame(object):
    def _read(self, *args, **kwargs):
        return self._pwt._read(*args, **kwargs)

    def __init__(self, pwt):
        self._pwt = pwt

        self.subframe_count, = struct.unpack('>i', self._read(4))

        namelen = struct.unpack('B', self._read(1))[0]

        self.name = "" if namelen is 0 else\
                    self._read(namelen).decode('utf8')

        mata = struct.unpack('>4f', self._read(4*4))
        matb = struct.unpack('>4f', self._read(4*4))
        matc = struct.unpack('>4f', self._read(4*4))
        matd = struct.unpack('>4f', self._read(4*4))
        self.matrix = np.matrix([mata, matb, matc, matd])

        self.has_animation = bool(self._read(1)[0])
        self.has_visuals = bool(self._read(1)[0])
        print("FRAME: '%s'; Subframes: %s; Visuals: %s; Animation: %s"%\
              (self.name, self.subframe_count,
               self.has_visuals, self.has_animation))

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

        if self.has_visuals:
            self.visuals = ModelVisuals(self)
        else:
            self.visuals = None

        self.subframes = []
        for _ in range(self.subframe_count):
            subframe = ModelFrame(self._pwt)
            self.subframes.append(subframe)

    def __str__(self):
        represent = (
            ("Name", "name"),
            ("Matrix", "matrix"),
            #("HasAnimation", "has_animation"),
            #("HasVisuals", "has_visuals"),
            ("Animation", "animation"),
            ("Visuals", "visuals"),
            ("SubFrameCount", "subframe_count"),
            ("SubFrames", "subframes"),
        )
        return do_str(self, represent)

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
        self.texturecount = self._read(1)[0]

        ###### VERTICES ######

        maxbbox_dimen = max((
            self._pwt.global_max[0] - self._pwt.global_min[0],
            self._pwt.global_max[1] - self._pwt.global_min[1],
            self._pwt.global_max[2] - self._pwt.global_min[2],
        ))

        bf = BitfieldReader(self._pwt._f)
        self.vertexcount, = struct.unpack('>i', bf.readbits(32))
        self.vertexcomp_count, = struct.unpack('>i', bf.readbits(32))

        if self.vertexcount != self.vertexcomp_count:
            print(self.vertexcount, self.normalcount)
            print("FRAME COUNT", self.subframe_count)
            raise Exception("Don't know how to handle compressed vectors")

        self.bboxMIN = struct.unpack('>3f', bf.readbits(3*4*8))

        bbx = struct.unpack('>B', bf.readbits(6))[0]
        bby = struct.unpack('>B', bf.readbits(6))[0]
        bbz = struct.unpack('>B', bf.readbits(6))[0]

        self.vertex_unused_bits = (bbx, bby, bbz)

        scaled_vertices = []
        for _ in range(self.vertexcount):
            x = bf.readbits(self._pwt.vertex_bit_accuracy-bbx)
            x = b'\x00'*(4-len(x)) + x
            y = bf.readbits(self._pwt.vertex_bit_accuracy-bby)
            y = b'\x00'*(4-len(y)) + y
            z = bf.readbits(self._pwt.vertex_bit_accuracy-bbz)
            z = b'\x00'*(4-len(z)) + z

            x = struct.unpack('>i', x)[0]
            y = struct.unpack('>i', y)[0]
            z = struct.unpack('>i', z)[0]

            scaled_vertices.append((x,y,z))

        oddbitnum = (1 << self._pwt.vertex_bit_accuracy) - 1
        self.vertices = [((v[0]*maxbbox_dimen/oddbitnum) + self.bboxMIN[0],
                     (v[1]*maxbbox_dimen/oddbitnum) + self.bboxMIN[1],
                     (v[2]*maxbbox_dimen/oddbitnum) + self.bboxMIN[2])
        for v in scaled_vertices]

        ########## NORMALS ##########
        bf = BitfieldReader(self._pwt._f)

        self.normalcount, = struct.unpack('>i', bf.readbits(32))
        self.normalcomp_count, = struct.unpack('>i', bf.readbits(32))

        if self.normalcount != self.normalcomp_count:
            raise Exception("Don't know how to handle compressed vectors")

        self.norm_bboxMIN = struct.unpack('>3f', bf.readbits(3*4*8))
        #Only needed for non vertices..... or something
        self.norm_bboxMAX = struct.unpack('>3f', bf.readbits(3*4*8))

        norm_bbx = struct.unpack('>B', bf.readbits(6))[0]
        norm_bby = struct.unpack('>B', bf.readbits(6))[0]
        norm_bbz = struct.unpack('>B', bf.readbits(6))[0]
        self.normal_unused_bits = (norm_bbx, norm_bby, norm_bbz)


        scaled_normals = []
        for _ in range(self.normalcount):
            x = bf.readbits(self._pwt.normal_bit_accuracy-norm_bbx)
            x = b'\x00'*(4-len(x)) + x
            y = bf.readbits(self._pwt.normal_bit_accuracy-norm_bby)
            y = b'\x00'*(4-len(y)) + y
            z = bf.readbits(self._pwt.normal_bit_accuracy-norm_bbz)
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

        maxnum = (1 << self._pwt.normal_bit_accuracy) - 1
        self.normals = [
            ((v[0]*maxbbox_dimen_normals/maxnum) + self.norm_bboxMIN[0],
             (v[1]*maxbbox_dimen_normals/maxnum) + self.norm_bboxMIN[1],
             (v[2]*maxbbox_dimen_normals/maxnum) + self.norm_bboxMIN[2])
            for v in scaled_normals]

        ############### FACES ###############

        face_vertex_bit_length = math.ceil(math.log2(self.vcount))
        face_normal_bit_length = math.ceil(math.log2(self.ncount))
        print("VCOUNT", self.vcount)
        print("NCOUNT", self.ncount)
        print("FACE BITS", face_vertex_bit_length, face_normal_bit_length)

        #raise Exception(face_vertex_bit_length)
        bf = BitfieldReader(self._pwt._f)

        self.faces = []
        self.facenormals = []
        for _ in range(self.fcount):
            face_ints = []
            normal_ints = []
            for _ in range(3):
                tmp = bf.readbits(face_vertex_bit_length)
                n = struct.unpack('>i', b'\x00'*(4-len(tmp)) + tmp)[0]
                normal_ints.append(n)

                tmp = bf.readbits(face_normal_bit_length)
                v = struct.unpack('>i', b'\x00'*(4-len(tmp)) + tmp)[0]
                face_ints.append(v)

            self.faces.append(tuple(face_ints))
            self.facenormals.append(tuple(normal_ints))

        ############### TEXMAP ###############

        texmapU = []
        for _ in range(self.vcount):
            texmapU.append(struct.unpack('>i', self._read(4))[0])

        texmapV = []
        for _ in range(self.vcount):
            texmapV.append(struct.unpack('>i', self._read(4))[0])

        ############### FACE DETAIL ###############

        #showpoints(self.vertices)
        #showpoly(self.vertices, self.faces)
        self.face_details = []
        try:
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
        except:
            self.face_details.append("HIT EOF")

        ############### TEXTURES ###############
        try:
            self.textures = None
            if self.texturecount:
                self.textures = []
                datlen = self._read(1)[0]
                for _ in range(self.texturecount):
                    self.textures.append(self._read(datlen))
        except:
            self.textures.append("HIT EOF")

    def __str__(self):
        represent = (
            ("VisualsVcount", "vcount"),
            ("VisualsNcount", "ncount"),
            ("VisualsFcount", "fcount"),
            ("Vertexcount", "vertexcount"),
            ("CompressevVcount", "vertexcomp_count"),
            ("Normalcount", "normalcount"),
            ("CompressevNcount", "normalcomp_count"),
            ("FaceCount", "fcount"),
            ("Texturecount", "texturecount"),
            ("bboxMIN", "bboxMIN"),
            ("VertexUnusedBits", "vertex_unused_bits"),
            ("NormalUnusedBits", "normal_unused_bits"),
            ("Vertices", "vertices"),
            ("Normals", "normals"),
            ("Faces", "faces"),
            ("FacesNormals", "facenormals"),
            ("FaceDetails", "face_details"),
            ("Textures", "textures"),
        )
        return do_str(self, represent)

def do_str(instance, represent):
    max_name_len = max((len(fi[0]) for fi in represent))
    s = []
    for name, field in represent:
        value = getattr(instance, field)
        if isinstance(value, list):
            if not len(value):
                s.append(("{:<%s}: []" % max_name_len).format(name))
            else:
                s.append(("{:<%s}:" % max_name_len).format(name))
                for item in value:
                    item = str(item).splitlines()
                    s += tuple(("  "+v for v in item))
        else:
            value = str(value).splitlines()
            if len(value) is 1:
                s.append(("{:<%s}: {}" % max_name_len)\
                         .format(name, value[0]))
            else:
                s.append(("{:<%s}:" % max_name_len)\
                         .format(name))
                s += tuple(("  "+v for v in value))

    return "\n".join(s)

def showpoly(vertices, faces):
    import matplotlib.pyplot as plt
    import mpl_toolkits.mplot3d as a3
    ax = a3.Axes3D(plt.figure())
    print(faces)

    facevertices = [(vertices[ai], vertices[bi], vertices[ci])
                    for ai,bi, ci in faces]

    print(facevertices)
    for face in facevertices:
        tri = a3.art3d.Poly3DCollection([
            face
            #for face in facevertices
        ])
        ax.add_collection3d(tri)

    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    ax.set_xlim(-2,2)
    ax.set_ylim(-2,2)
    ax.set_zlim(-2,2)

    plt.show()

def showpoints(points):
    from mpl_toolkits.mplot3d import Axes3D
    import matplotlib.pyplot as plt

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.set_aspect("equal")

    xs = [elem[0] for elem in points]
    ys = [elem[2] for elem in points]
    zs = [elem[1] for elem in points]

    ax.scatter(xs, ys, zs)

    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')

    plt.show()

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
        print("\nConsumed Bytes:", f.tell(), hex(f.tell()))
        f.seek(0, os.SEEK_END)
        print("Total Bytes:   ", f.tell(), hex(f.tell()))

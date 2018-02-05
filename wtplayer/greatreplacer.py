#!/usr/bin/python3

import os
import sys
import re

renamer_new = re.compile(r"new (WT[\w]*)")
renamer_ret = re.compile(r"(public |protected |private |\(|, )(WT[\w]*) ")
renamer_cst = re.compile(r", (WT[\w]+)\.getCPtr\(([a-zA-z_][a-zA-Z_0-9]*)\), ")
renamer_cpt = re.compile(r"protected static long getCPtr\(([a-zA-z_][a-zA-Z_0-9]*) obj\)")
renamer_cls = re.compile(r"public class ([a-zA-z_][a-zA-Z_0-9]*)( extends ([a-zA-z_][a-zA-Z_0-9]*))* {")

CPTR_Wrap = """\
  protected static long getCPtr(wildtangent.webdriver.{0} obj) {{
    wildtangent.webdriver.impl.{0} objimpl = (wildtangent.webdriver.impl.{0}) obj;
    return getCPtr(({0})objimpl);
  }}\n\n"""

def process_normal(filename_in, filename_out, verbose=False):
    with open(filename_in) as f:
        lines = f.readlines()

    with open(filename_out, 'w') as fout:
        for i, line in enumerate(lines):
            if("protected static long getCPtr" in line):
                clsname_match = renamer_cpt.search(line)
                if(clsname_match):
                    clsname = clsname_match.group(1)
                    if clsname not in ("WTEvent"):
                        fout.write(CPTR_Wrap.format(clsname))
            else:
                line = renamer_new.sub(r'new wildtangent.webdriver.impl.\1', line)
                line = renamer_ret.sub(r'\1wildtangent.webdriver.\2 ', line)
                line = renamer_cst.sub(r', \1.getCPtr((\1)\2), (\1)', line)
                line = renamer_cls.sub(r'public abstract class \1\2 implements wildtangent.webdriver.\1 {', line)
                line = line.replace(", Bitmap_To_Use_As_Drop",
                                    ", (wildtangent.webdriver.impl.WTBitmap)Bitmap_To_Use_As_Drop")

            if verbose:
                print(line[:-1])
            fout.write(line)

def process_intermediary(filename_in, filename_out, verbose=False):
    with open(filename_in) as f:
        lines = f.readlines()

    renamer_dir = re.compile(r"jself.run((event == 0) ? null : new wildtangent.webdriver.impl.WTEvent(event, false));")

    with open(filename_out, 'w') as fout:
        for i, line in enumerate(lines):
            if line == "    jself.run((event == 0) ? null : new WTEvent(event, false));\n":
                line = "    jself.run((event == 0) ? null : new wildtangent.webdriver.impl.WTEvent(event, false));\n"
            if line == "    jself.run((o == 0) ? null : new WTObject(o, false));\n":
                line = "    jself.run((o == 0) ? null : new wildtangent.webdriver.impl.WTObject(o, false));\n"

            if verbose:
                print(line[:-1])
            fout.write(line)


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("infile")
    parser.add_argument("outfile")
    parser.add_argument('--verbose', dest='verbose', action='store_true')
    parser.add_argument('--swigintermediary', dest='func', action='store_const',
                        default=process_normal, const=process_intermediary)
    parser.set_defaults(verbose=False)
    args = parser.parse_args()
    if(args.verbose):
        print("Processing: " + args.infile)
    args.func(args.infile, args.outfile, args.verbose)

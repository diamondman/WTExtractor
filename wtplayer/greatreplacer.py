#!/usr/bin/python3

import os
import sys
import re

def main(filename, verbose=False):
    print("Processing: " + filename)
    with open(filename) as f:
        lines = f.readlines()

    renamer_new = re.compile(r"new (WT[\w]*)")
    renamer_ret = re.compile(r"(public |protected |private |\(|, )(WT[\w]*) ")
    renamer_cst = re.compile(r", (WT[\w]+)\.getCPtr\(([a-zA-z_][a-zA-Z_0-9]*)\), ")

    with open(filename, 'w') as fout:
        for i, line in enumerate(lines):
            #if "new WT" in line:
            if("protected static long getCPtr" not in line):
                line = renamer_new.sub(r'new wildtangent.webdriver.impl.\1', line)
                line = renamer_ret.sub(r'\1wildtangent.webdriver.\2 ', line)
                line = renamer_cst.sub(r', \1.getCPtr((\1)\2), (\1)', line)

            if verbose:
                print(line[:-1])
            fout.write(line)


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("infile")
    parser.add_argument('--verbose', dest='verbose', action='store_true')
    parser.set_defaults(verbose=False)
    args = parser.parse_args()
    main(args.infile, args.verbose)

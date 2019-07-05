from collections import Counter
import gzip
import numpy as np
import math


TABLE = {
    'A': 0,
    'C': 1,
    'G': 2,
    'T': 3
    }

INV_TABLE = {
    0: 'A',
    1: 'C',
    2: 'G',
    3: 'T'
    }

def rolling_hash(s):
    n = 0
    ctr = Counter()
    for i, c in enumerate(s):
        v = TABLE.get(c, None)
        if v is None:
            continue
        n <<= 2
        n += v
        n &= 0xffff
        ctr[n] += 1
    for n, val in ctr.most_common(100):
        print(convert_2bit_to_kmer(n), val)
        
def convert_kmer_to_2bit(kmer):
    n = 0
    for c in kmer:
        v = TABLE.get(c, None)
        if v is None:
            raise RuntimeError
        n <<= 2
        n += v
    return n

def convert_2bit_to_kmer(b):
    k = []
    for i in range(8):
        k.append(INV_TABLE[b & 0b11])
        b >>= 2
    return ''.join(k)[::-1]

def convert_to_2bit(s):
    c = Counter()
    for i in range(0, len(s), 8):
        kmer = s[i:i+8]
        try:
            n = convert_kmer_to_2bit(kmer)
        except RuntimeError:
            pass
        else:
            c[n] += 1
    return c

def main():
    with gzip.GzipFile("hg38.fa.gz") as f:
        accum = []
        c = None
        while f:
            line = f.readline()
            if line.startswith(">"):
                if c is not None:
                    s = ''.join(accum)
                    print("Read", c, "with", len(s))
                    rolling_hash(s)
#                    ctr = convert_to_2bit(s)
#                    for n, val in ctr.most_common(25):
#                        print(convert_2bit_to_kmer(n), val)

                c = line[1:].strip()
            else:
                accum.append(str.upper(line.strip()))

if __name__ == '__main__':
    main()

import os
import re
from joblib import Parallel, delayed



def process_file (filepath, odir):
    with open(filepath, "r") as files:
        for line in files:
            line = line.rstrip()
            elem = line.split('/')
            sn = elem[5]

            print(line, file=open(odir + sn+".files","a"))


def main():
    idir = "/dsl/David_Kyle_Creativeness/XML_textblocks/batch-filenames/"
    odir = "/dsl/David_Kyle_Creativeness/XML_textblocks/sn-filenames/"

    files = [os.path.join(idir, f) for f in os.listdir(idir)]

    Parallel(n_jobs=80)(delayed(process_file)(f, odir) for f in files)

if __name__ == "__main__":
    main()



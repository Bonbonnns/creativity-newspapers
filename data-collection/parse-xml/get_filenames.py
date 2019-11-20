import os
import re
from joblib import Parallel, delayed


def get_subdirectories(rootpath):
    sdirs = [os.path.join(rootpath,d) for d in os.listdir(rootpath) if os.path.isdir(os.path.join(rootpath,d))]
    return sdirs

def from_root_get_batches (rootpath):
    batches = [os.path.join(rootpath,d) for d in os.listdir(rootpath) if os.path.isdir(os.path.join(rootpath,d)) and "batch" in d]
    return batches

def process_batch(path, odir):
    ofile = open(odir + "/" + path.split('/')[-1] + ".files", "w")
    sns = get_subdirectories(path)
    for s in sns:
        print(s)
        short = s.split('/')[-1]
        yrs = get_subdirectories(s)
        for y in yrs:
            ms = get_subdirectories(y)
            for m in ms:
                ds = get_subdirectories(m)
                for d in ds:
                    eds = get_subdirectories(d)
                    for ed in eds:
                        seqs = get_subdirectories(ed)
                        for seq in seqs:
                            fnames = [os.path.join(seq,f) for f in os.listdir(seq) if ".xml" in f]
                            for f in fnames:
                                print(f, file=ofile)

                                
    print("finished processing: ", path)
    return

#
#    levels deep:
#        0       batches
#        1       sns (sn8-10 digits, or 10 digits)
#        2       year
#        3       month
#        4       day
#        5       ed
#        6       seq
#        7       files
#

rdir = "/dsl/David_Kyle_Creativeness/xml/"
odir = "./files/"
batches = from_root_get_batches(rdir)
Parallel(n_jobs=80)(delayed(process_batch)(b, odir) for b in batches)

# given search word, window size and info and content file, extract the window around the search term in each document that has it. 
searchword = "talent"
window = 20
ifile = open("/dsl/David_Kyle_Creativeness/raw_corpus/info_and_content.tsv", "r")
ofile = open("./data/talent_kwic.tsv", "w")

def construct_loc_url (sn, filename):
    # url example: https://chroniclingamerica.loc.gov/lccn/sn86063539/1919-10-24/ed-1/seq-1/
    base = "https://chroniclingamerica.loc.gov/lccn/"

    # from filename extract date, ed, seq
    elem = filename.split("_")
    date = elem[0]
    ed = elem[1]
    seq = elem[2]

    url = base + sn + "/" + date + "/" + ed + "/" + seq + "/"
    return (url)

for line in ifile:
    line = line.rstrip()
    elements = line.split('\t')

    if len(elements) < 6: continue

    batch = elements[1]
    sn = elements[2]
    filename = elements[3]
    content = elements[5]

    if searchword in content:
        words = content.split()
        index = -1
        for i,w in enumerate(words):
            if w == searchword:
                index = i
                break

        if index != -1:
            first = index - window
            last = index + window + 1
            
            if first < 0: first = 0
            if last > len(words): last = len(words)

            result = " ".join(words[first:last])

            year = filename.split('-')[0]
            url = construct_loc_url(sn, filename)
            print(year + "\t" + url + "\t" + elements[0] + "\t" + batch + "\t" + sn + "\t" + filename +"\t" + result, file=ofile)

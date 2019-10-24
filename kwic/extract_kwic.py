# given search word, window size and info and content file, extract the window around the search term in each document that has it. 
searchword = "talent"
window = 20
ifile = open("/dsl/David_Kyle_Creativeness/raw_corpus/info_and_content.tsv", "r")

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
            print(year + "\t" + elements[0] + "\t" + batch + "\t" + sn + "\t" + filename +"\t" + result)







# Given the info and content file, get counts of number of documents / year
ifile = open("/dsl/David_Kyle_Creativeness/raw_corpus/info_and_content.tsv", "r")

counts = {}
for line in ifile:
    line = line.rstrip()
    elements = line.split('\t')


    filename = elements[3]
    year = filename.split('-')[0]
    if year in counts: counts[year] = counts[year] + 1
    else: counts[year] = 1

years = counts.keys()
years = sorted(years)
for y in years:
    print(y + "," + str(counts[y]))


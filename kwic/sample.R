# randomly sample from the kwic rows extracted with extract_kwic.py
library(data.table)

samplesize = 100

get_sample = function(year)  {
    subset = data[data$V1 == year]
    if (dim(subset)[1] < samplesize) { 
        return (subset)
    }

    return (subset[sample(nrow(subset), samplesize), ])
}

data = fread("./data/talent_kwic.tsv", sep="\t", header=FALSE, stringsAsFactors=FALSE)
years = sort(unique(data$V1))
subsets = lapply(years[years < 1926], get_sample)
combined = do.call("rbind", subsets)

write.table(combined, file="./data/sample_talent_kwic.csv", sep=",", quote=TRUE)

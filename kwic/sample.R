# randomly sample from the kwic rows extracted with extract_kwic.py
library(data.table)

get_sample = function(year)  {
    subset = data[data$V1 == year]
    if (dim(subset)[1] < 100) { 
        return (subset)
    }

    return (subset[sample(nrow(subset), 100), ])
}

data = fread("talent.tsv", sep="\t", header=FALSE, stringsAsFactors=FALSE)
years = sort(unique(data$V1))
subsets = lapply(years[years < 1926], get_sample)
combined = do.call("rbind", subsets)

write.table(combined, file="kwic_talent_all_years.csv", sep=",", quote=TRUE)

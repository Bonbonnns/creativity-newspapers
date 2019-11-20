library("xml2", lib.loc="~/r_libs")
library("jsonlite", lib.loc="~/r_libs")

# ----------------- #
# -- USER DEFINE -- #
# ----------------- #

# Folder to save zip files to. Note: this is >1TB of data, so please be sure
# you have space!
DEST_DIR = "../../tarzip"


# --------------- #
# -- FUNCTIONS -- #
# --------------- #

log = function(msg, indent = 0) {
    # Update console with custom message and current datetime
    tab = ifelse(indent==0, " ", paste0(rep("    ", indent), collapse = ""))
    cat(sprintf("%s%s%s\n", Sys.time(), tab, msg))
}


# ---------------------- #
# -- OPERATIONAL CODE -- #
# ---------------------- #

# No scientific notation
options(scipen = 999)

# Start program timing
start_time = Sys.time()

# Make sure DEST_DIR does not end in a slash
DEST_DIR = gsub("\\/$", "", DEST_DIR)

# URLs
JSON_URL = "https://chroniclingamerica.loc.gov/ocr.json"

# Download JSON ocr table
ocr_table = fromJSON(paste(readLines(JSON_URL), collapse=""))[[1]]

# Append batch to the name
ocr_table$name = paste0("batch_", ocr_table$name)

# Filter out already-downloaded .tar.bz2 files (if running program repeatedly)
existing_bz2 = list.files(DEST_DIR, pattern = "\\.tar\\.bz2")
if(length(existing_bz2)) {
    ocr_table = ocr_table[!ocr_table$name %in% existing_bz2,]
}

# Convert sizes to GB
ocr_table$size = ocr_table$size / 1000000

# Loop through each URL and download to destination directory
log("Beginning download...")
log(sprintf("Total files to download: %s", length(ocr_table$name)))
log(sprintf("Total data to download: %s GB", round(sum(ocr_table$size))))
log("--------------------------------------")
log("")

for(i in 1:length(ocr_table$name)) {
    
    # Construct destination filename
    base = ocr_table$name[i]
    filename = paste0(DEST_DIR, "/", base)
    
    # Attempt to determine estimated program completion time, based on the time
    # it took all prior downloads to complete
    time_elapsed = difftime(Sys.time(), start_time)
    units(time_elapsed) = "secs"
    GB_remaining = sum(ocr_table$size[i:length(ocr_table$name)])
    GB_done = ifelse(i==1, 0, sum(ocr_table$size[1:(i-1)]))
    GB_done_per_sec = GB_done / as.numeric(time_elapsed)
    est_time_remaining = GB_remaining / GB_done_per_sec  # in seconds
    est_time_remaining = round(est_time_remaining / 3600, 2)  # in hours
    
    # Percentage of data downloaded
    pct_done = round(100*(GB_done/sum(ocr_table$size)), 2)
    
    # Notify which batch is being downloaded
    log(sprintf("BATCH: '%s'\nFILEID: %s\nSIZE: %sGB\nPCTDONE: %s%%\nESTTIME: %s hours",
                gsub("\\.tar\\.bz2", "", base),
                i,
                ocr_table$size[i],
                pct_done,
                est_time_remaining))
    
    # Attempt download
    tryCatch({
        download.file(ocr_table$url[i], destfile = filename, quiet = TRUE)
        system(sprintf("curl -O %s", ocr_table$url))
        log("SUCCESS", indent = 1)
    }, error = function(e) {
        message(sprintf("ERROR in file '%s'", base))
        message(e)
    })
}

log("")
log("--------------------------------------")
log("All downloads complete")

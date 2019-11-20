# Introduction 

Using code from Andoni, Chandni and Arthur.  

This repository hosts the code for the data collection and extraction part of the Newspaper's project.  

Go to the Google Drive Project Folder for a the workflow diagram as well as README explaining the steps in more detail.  

# 1. Getting the Data

The directory 'get-xml' contains the code used to get the data from the library of congress website.  

+ **dl_batches.R** Downloads all the batches list at [chroniclingamerica.loc.gov/ocr.json](https://chroniclingamerica.loc.gov/ocr.json).
+ **unzip_parallel.sh** Extracts the files from the tar.bz2 archives. ls | unzip_parallel.sh

# 2. Parsing the Data  

The format of the data is unwieldy: it takes a long time to just walk through the directories to access each file. 
Each page from an issue is stored as two separate files - ocr.txt and ocr.xml. 
ocr.txt contains each TextLine that was extracted from the ocr on a different line.
ocr.xml contains the actual xml output of the ocr process using AbbeyFineReader.
We are interested in the TextBlocks not the TextLines.
So, we need to parse the xml files to get the TextBlocks.
There are millions of files, which is hard to deal with in Unix systems.
We need to merge the files into larger files while maintaining the information that was lost in the merge.
We do this by having two files for each serial number an info file and a txt file with the content. 
Each line in the txt file corresponds with the same line number in the info file.

The steps for parsing the data are:  

+ Get a list of all the filenames for each batch -- **get_filenames.py**
+ From that list create a list of filenames for each sn (unique id from library of congress) -- **batch2sn.py**
+ For each sn; parse all the xml files for the TextBlocks. save the txt and info -- **runner.sh**

# Contact

avkoehl at ucdavis dot edu


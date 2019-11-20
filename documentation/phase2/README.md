# INTRODUCTION

This README has the information about phase 2 of the Newspaper project.  
Code is in the Newspapers Project on Bitbucket  

The files in this folder:  
+ **workflow_diagram** --  The workflow diagram.
+ **phase2batches.txt** -- A file containing all of the batches included in this phase.  
+ **xml-parse/xml-errors.txt** -- A file containing the log of the xml parse, showing the failed files that need to be redownloaded.  

The main data directory on the server is /dsl/Chronicling_America/

# Highest Level Directories

| Name                | Info           
| :------------       |:-------------
| tarzip/             | Directly downloaded from site, each batch in .tar.bz2
| xml/                | The extracted data from tarzip.
| textblock_content/  | Contains the parsed data from xml.


# 1. 'xml'
The 'xml' directory contains all of the batches that we have downloaded. Currently there are 1864 batches.
Note that new batches are added periodically to the loc site. In addition new versions of existing batches are also added to the site.  

This corpus of newspapers is massive and hard to deal with. This document shows the steps for organizing the collection and making it accessible for text mining.


Each batch is divided into a bunch of subdirectories. Each column is a directory or list of files.
Here is the hierarchy for batch_ak_albatross_ver01 as an example.

| batch name                           | LCCN         | year  | month  | day  | ed    | seq    | files           
| :------------------------------------|:-------------|:------|:-------|:-----|:------|:-------|:----
| batch_ak_albatross_ver_01/           | sn94050023/  | 1908/ | 08/    | 01/  | ed-1/ | seq-1/ | ocr.txt
| batch_ak_albatross_ver_01/           | sn94050023/  | 1908/ | 08/    | 01/  | ed-1/ | seq-1/ | ocr.xml
| batch_ak_albatross_ver_01/           | sn94050023/  | 1908/ | 08/    | 01/  | ed-1/ | seq-2/ | ocr.txt
| batch_ak_albatross_ver_01/           | sn94050023/  | 1908/ | 08/    | 01/  | ed-1/ | seq-2/ | ocr.xml
| batch_ak_albatross_ver_01/           | sn94050023/  | 1908/ | 09/    | 01/  | ed-1/ | seq-1/ | ocr.txt
| batch_ak_albatross_ver_01/           | sn94050023/  | 1908/ | 09/    | 01/  | ed-1/ | seq-1/ | ocr.xml

... and so on

Note some batches contain more than one LCCN.  

The subdirectories match with how the loc.gov site stores the data. 
For example, given a file /lccn/sn97067598/1919-05-28/ed-1/seq-1/ocr.xml you can view on the site at [loc.gov/lccn/sn97067598/1910-05-28/ed-1/seq-1/](https://chroniclingamerica.loc.gov/lccn/sn97067598/1919-05-28/ed-1/seq-1/)  

The **'ed'** field I think refers to edition, **'seq'** seems to refer to the page number. ocr.txt should have just the text, and ocr.xml has the ocr text and other data output from the ocr software such as 'textblock' which we need.  

List of programs used to scrape and extract this:
+ dl_batches (written by Andoni and rerun by Chandni)
+ unzip_parallel.sh (written by and run by Chandni)


# 2. 'textblock_content'

The data stored in 'xml' is in the exact format it was downloaded. 
However, it is not easy to iterate through the files and clean them for example. 
Also, the batches are not very descriptive or useful, we would rather have the corpus split by LCCN.
In addition, we want to maintain each 'textblock' from the ocr as distinct documents. 
So, the target file structure looks like this:  

| LCCN              |  each line
|:------------------|:----------------
| sn94050023.info   | 1908,08,01,ed-1,seq-1
| sn94050023.txt    | one text block

... and so on

Where each .info and .txt file contains the same number of lines.

To get to this state we need to parse the xml to get the text blocks and we need to create a new file to save these in.
This was done with **parse-xml** code from the **data-collection** repo on Bitbucket in the Newspapers Project.  

Directory Structure for 'textblock_content':  
| dir name       | description
|:---------------|:----------------------------------------------------------------------------------
|batch-filenames | For each batch, list all the xml files within
|sn-filenames    | For each sn, list all the xml files within
|info            | For each sn, all the metadata for the textblock (lines correspond with /text/)
|text            | For each sn, all the text content for the textblock (lines coorespond with /info/)
|log             | For each sn, show number of succesfully extracted textblocks from each xml file
<!--stackedit_data:
eyJoaXN0b3J5IjpbMjM2MjYwNDI5XX0=
-->
# INTRODUCTION: Newspaper Project  

The Library of Congress hosts newspapers collected in the United States from 1789 to 1963. All newspapers up to 1923 are in the public domain.
They offer the digitized version of these newspapers and their issues online. In general they have a high quality scan of the page as well as the ocr results.
You can access them at [loc.gov](https://chroniclingamerica.loc.gov/#tab=tab_newspapers). 

The effort of running ocr and digitizing the papers has been handled by many different institutions.
These efforts are handled in 'batches'. Each 'batch' containing a set of ocred files. You can browse the batches at [loc.gov/batches](https://chroniclingamerica.loc.gov/batches/)
We have used their api to download the complete collection.  

# PHASE 1

Phase 1 refers to all the work done from 2017 to May of 2019 by Andoni, Arthur, Jonathan, and Chandni. 
The goal was to study the usage of key words determined by David Kyle such as 'creative', 'creativeness', and 'talent'.
Refer to the Phase 1 folder README to know more.
In brief, phase 1 involved 234 batches from the chronicling america corpus. 
The batches were processed, cleaned and lemmatized and then topic modeled.  

This work is now being done by Bonnie, David Kyle's student, and is no longer an active project for the dsl/dsi.

# PHASE 2

Phase 2 is the current work being done on this project and expands the scope and scale of phase 1.
The idea is to download all the batches that phase 1 missed, and to explore methods of tracking changes in the corpus with respect to historical context, geographic location, and factors of the newspapers themselves.
Refer to the Phase 2 folder README for more.


# FILES

**LCCN_Metadata.csv**  -- contains the metadata for each 'sn' of the corpus.  
**batches.json** -- contains the links to all the ocred batches of the corpus.  


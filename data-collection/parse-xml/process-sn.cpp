#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "./include/rapidxml.hpp"
#include "./include/rapidxml_utils.hpp"

std::vector <std::string> process_file(const char* fpath);
std::vector <std::string> strsplit(std::string str, std::string delim);

// for each sn
int main (int argc, char** argv)
{
    std::string odir = "/dsl/David_Kyle_Creativeness/XML_textblocks/";
    std::vector <std::string> files;
    std::ifstream inputfile;
    inputfile.open(argv[1]);

    std::string line;
    while(std::getline(inputfile, line))
    {
        files.push_back(line);
    }//while

    // for each sn delete the logfile textfile and infofile
    std::vector<std::string> temp = strsplit(std::string(argv[1]), "/");
    std::string full = temp[5];
    temp = strsplit(full, "."); 
    std::string sn = temp[0];
    std::string tpath = odir + "/text/" + sn + ".txt";
    std::string ipath = odir + "/info/" + sn + ".dat";
    std::string lpath = odir + "/log/" + sn + ".dat";
    std::remove(tpath.c_str());
    std::remove(ipath.c_str());
    std::remove(lpath.c_str());
    
    // FOR EACH FILE
    for (size_t i = 0; i < files.size(); i++)
    {
        const char* filename = files[i].c_str();
        std::vector <std::string> parsed;
        parsed = strsplit(std::string(filename), "/");

        std::vector <std::string> tb;
        tb = process_file(filename);

        // batch = parsed[4], sn = parsed[5], date = parsed[6-8], ed=parsed[9], page=parsed[10]
        std::string info = parsed[4] + " " + parsed[5] + " " + parsed[6] + "-" + parsed[7] + "-" + parsed[8] + " " + parsed[9] + " " + parsed[10];
        std::string textfilepath = odir + "text/" + parsed[5] + ".txt";
        std::string infofilepath = odir + "info/" + parsed[5] + ".dat";
        std::string logfilepath = odir + "log/" + parsed[5] + ".dat";

        std::ofstream tfile;
        std::ofstream ifile;
        std::ofstream lfile;
        tfile.open(textfilepath.c_str(), std::ios::app);
        ifile.open(infofilepath.c_str(), std::ios::app);
        lfile.open(logfilepath.c_str(), std::ios::app);

        if (!(tfile.is_open() && ifile.is_open() && lfile.is_open()))
            return 1;

        for(size_t i = 0; i != tb.size(); i++) {
            tfile << tb[i] << "\n";
            ifile << info << " " << (i+1) << "\n";
        }

        lfile << filename << " " << tb.size() << "\n";

        tfile.close();
        ifile.close();
        lfile.close();
    }// for each file


    std::cout << "finished processing: " << sn << std::endl;
    return 0;
}// main

std::vector <std::string>  process_file(const char* fpath)
{
    std::vector <std::string> textblocks;

    rapidxml::file<> xmlFile(fpath);
    rapidxml::xml_document<> doc;
    try {
        doc.parse<rapidxml::parse_full>(xmlFile.data());    
    }

    catch (const std::runtime_error& e)
    {
        std::cout << "ERROR: Runtime error was: " << e.what() << " " << fpath << std::endl;
        return textblocks;
    }
    catch (const rapidxml::parse_error& e)
    {
        std::cout << "ERROR: Parse error was: " << e.what() << " " << fpath << std::endl;
        return textblocks;
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: Error was: " << e.what() << " " << fpath << std::endl;
        return textblocks;
    }
    catch (...)
    {
        std::cout << "ERROR: An unknown error occurred." << std::endl;
        return textblocks;
    }


    rapidxml::xml_node<>* alto =  doc.first_node("alto");
    rapidxml::xml_node<>* layout =  alto->first_node("Layout");
    rapidxml::xml_node<>* page =  layout->first_node("Page");
    rapidxml::xml_node<>* pspace =  page->first_node("PrintSpace");

    // iterate over the text blocks
    for (rapidxml::xml_node<>* tb = pspace->first_node("TextBlock"); tb; tb = tb->next_sibling("TextBlock"))
    {// for each text block 
        std::string textblockcontent = "";
        for (rapidxml::xml_node<>* tl = tb->first_node("TextLine"); tl; tl = tl->next_sibling("TextLine"))
        {// iterate through the TextLine(s)

            for (rapidxml::xml_node<>* str = tl->first_node("String"); str; str = str->next_sibling("String"))
            {// iterate through the String(s)
                if (textblockcontent != "")
                    textblockcontent = textblockcontent + " " + str->first_attribute("CONTENT")->value();
                else
                    textblockcontent = str->first_attribute("CONTENT")->value();
            }//for each string
        } // for each line

        if (textblockcontent != "")
            textblocks.push_back(textblockcontent);
    }// for each block

    return textblocks;
}

std::vector <std::string> strsplit(std::string str, std::string delim)
{
    std::vector <std::string> elements;
    size_t pos = 0;
    std::string elem;
    while ((pos = str.find(delim)) != std::string::npos) {
        elem = str.substr(0, pos);
        elements.push_back(elem);
        str.erase(0, pos + 1);
    }
    elements.push_back(str);
    return elements;
}

#include "Fileloader.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <dirent.h>


Fileloader::Fileloader()
{
    //ctor
}

Fileloader::~Fileloader()
{
    //dtor
}

std::vector<std::string> Fileloader::Loadfile(std::string filename)
{
    std::fstream loader;
    std::string line;
    const char* path = filename.c_str();
    std::vector<std::string> data;
    loader.open(path,std::ios::in);
    if(loader.good())
    {
        while(!loader.eof())
        {
            std::getline(loader,line);
            if(line.compare(0,2,"//")!=0)
            {
                //std::cout<<line<<std::endl;
                for(int a = line.size()-1;a>=0;--a)
                {
                    int b= int(line[a]);
                    switch(b)
                    {
                        case -2:
                            line.erase(a);
                            break;
                        case -1:
                            line.erase(a);
                            break;
                        case 0:
                            line.erase(a);
                            break;
                        case 13:
                            line.erase(a);
                            break;
                        //default:
                            //std::cout<<b<<"|";
                    }

                }
                //std::cout<<std::endl;
                data.push_back(line);
            }
        }
    }
    loader.close();
    return(data);
}

void Fileloader::Writefile(std::string filename,std::vector<std::string> data)
{
    std::fstream loader;
    const char* path = filename.c_str();
    loader.open(path,std::ios::out);
    if(loader.good())
    {
        for(std::vector<std::string>::iterator a = data.begin();a!=data.end();++a)
        {
            loader<<(*a);
            if(a!=data.end()-1)
            {
                loader<<std::endl;
            }
        }

    }
    loader.close();
}

std::vector<std::string> Fileloader::ScanFile(char* adir)
{
    DIR* dir;
    struct dirent* entry;
    dir = opendir(adir);
    std::vector<std::string> files;
    do
    {
        entry = readdir(dir);
        if(entry)
        {
           files.push_back(entry->d_name);
        }
    }
    while(entry);
    closedir(dir);
    return(files);
}

std::vector<std::string> Fileloader::ScanFile(char* adir,std::string type)
{
    DIR* dir;
    struct dirent* entry;
    dir = opendir(adir);
    std::vector<std::string> files;
    do
    {
        entry = readdir(dir);
        if(entry)
        {
            std::string file = entry->d_name;
            int found = file.find_last_of(".");
            if(!type.compare(file.substr(found+1)))
            {
                files.push_back(file);
            }
        }
    }
    while(entry);
    closedir(dir);
    return(files);
}

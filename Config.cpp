#include "Config.hpp"
#include "Fileloader.hpp"
#include <iostream>
#include <vector>
#include <sstream>



std::map<std::string,std::string> Config::config;

Config::Config()
{
    //ctor
}

Config::~Config()
{
    //dtor
}

void Config::load()
{
    std::vector<std::string>data = Fileloader::Loadfile("config.cfg");
    for(std::vector<std::string>::iterator it=data.begin();it!=data.end();++it)
    {
        std::string line = (*it);
        int found = line.find_last_of("=");
        Config::config.insert(std::pair<std::string,std::string>(line.substr(0,found),line.substr(found+1)));
        //std::cout<<"IN:"<<line.substr(0,found)<<":"<<line.substr(found+1)<<std::endl;
    }
}

float Config::getValue(std::string name)
{
    std::map<std::string,std::string>::iterator it = Config::config.find(name);
    if(it!=Config::config.end())
    {
        std::stringstream strtofloat;
        float value;
        strtofloat<<(*it).second;
        strtofloat>>value;
        //std::cout<<"OUT:"<<(*it).first<<":"<<value<<std::endl;
        return(value);
    }
    return (NULL);
}

float Config::getSpeed()
{
    std::map<std::string,std::string>::iterator it = Config::config.find("Speed");
    if(it!=Config::config.end())
    {
        std::stringstream strtofloat;
        float value;
        strtofloat<<(*it).second;
        strtofloat>>value;
        return(value);
    }
    return (1.0f);
}

std::string Config::getString(std::string name)
{
    std::map<std::string,std::string>::iterator it = Config::config.find(name);
    if(it!=Config::config.end())
    {
        return((*it).second);
    }
    return ("error");
}


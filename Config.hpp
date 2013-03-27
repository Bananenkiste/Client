#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <sfml/system.hpp>


class Config
{
    public:
        Config();
        virtual ~Config();
        static void load();
        static float getValue(std::string name);
        static std::string getString(std::string name);
    protected:
    private:
        static std::map<std::string,std::string> config;

};

#endif // CONFIG_H

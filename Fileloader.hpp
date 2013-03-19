#ifndef FILELOADER_H
#define FILELOADER_H

#include <string>
#include <vector>


class Fileloader
{
    public:
        Fileloader();
        virtual ~Fileloader();
        static std::vector<std::string> Loadfile(std::string filename);
        static void Writefile(std::string filename,std::vector<std::string>data);
        static std::vector<std::string> ScanFile(char* adir);
        static std::vector<std::string> ScanFile(char* adir,std::string type);

    protected:
    private:
};

#endif // FILELOADER_H

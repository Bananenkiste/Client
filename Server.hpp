#ifndef SERVER_H
#define SERVER_H

#include "sfml\graphics.hpp"
#include "sfml\window.hpp"

class Server
{
    public:
        Server(std::string aName,std::string aIp,int x, int y);
        virtual ~Server();

        void update(int x, int y);
        void draw(sf::RenderWindow* win);
        bool getActive();
        std::string getIp();

    private:

        sf::Sprite* normal;
        sf::Sprite* over;
        sf::Text label;
        bool active;

        std::string name;
        std::string ip;
};

#endif // SERVER_H

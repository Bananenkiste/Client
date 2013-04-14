#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <sstream>
#include <sfml/graphics.hpp>

class Player
{
    public:
        Player();
        Player(int aid,std::string aname);
        virtual ~Player();

        std::string getName();
        int getId();

        void setSocket(SOCKET asocket);
        void setPosition(sf::Vector2f npos);
        void setDir(int ndir);
        SOCKET getSocket();
        void update(float step);
        void setVariables();
        void draw(sf::RenderWindow* window);
        void drawLabel(sf::RenderWindow* win,float x,float y);
        void setActive();
        void setAlive(bool state);
        bool getAlive();

    protected:
    private:
        int id;
        std::string name;
        sf::Vector2f position;
        sf::Vector2f target;
        int dir;
        int tempdir;

        float speed;
        SOCKET socket;
        sf::Sprite* pawn;
        sf::Sprite* playerlabel1;
        sf::Sprite* playerlabel2;
        sf::Text label;
        bool active;
        bool alive;
};

#endif // PLAYER_H

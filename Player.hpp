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
        SOCKET getSocket();
        void update(float step);
        void setVariables();
        void draw(sf::RenderWindow* window);
        void drawLabel(sf::RenderWindow* win,float x,float y);
        void setActive();

    protected:
    private:
        int id;
        std::string name;
        sf::Vector2f position;
        SOCKET socket;
        sf::Sprite* pawn;
        sf::Sprite* playerlabel1;
        sf::Sprite* playerlabel2;
        sf::Text label;
        bool active;
};

#endif // PLAYER_H

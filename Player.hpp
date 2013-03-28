#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
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
        SOCKET getSocket();
        void update(float step);
        void setVariables();
        void draw();
        sf::Sprite getPlayerButton();

    protected:
    private:
        int id;
        std::string name;
        glm::mat3 position;
        SOCKET socket;
        sf::Sprite player;
        sf::Sprite playerbutton;
};

#endif // PLAYER_H

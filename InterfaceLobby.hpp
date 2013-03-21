#ifndef INTERFACELOBBY_H
#define INTERFACELOBBY_H

#include "Interface.hpp"

#include <sfml/window.hpp>
#include <sfml/graphics.hpp>


class InterfaceLobby : public Interface
{
    public:
        InterfaceLobby(sf::RenderWindow* aWindow);
        virtual ~InterfaceLobby();

        virtual void update(float step);
        virtual void draw(sf::RenderWindow* window);
        virtual void handleData(std::string data);
    protected:
        sf::RenderWindow* window;
        sf::Sprite* background;
};

#endif // INTERFACE_H

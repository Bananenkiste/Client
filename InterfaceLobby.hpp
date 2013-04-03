#ifndef INTERFACELOBBY_H
#define INTERFACELOBBY_H

#include "Interface.hpp"

#include <sfml/window.hpp>
#include <sfml/graphics.hpp>

class Button;

class InterfaceLobby : public Interface
{
    public:
        InterfaceLobby(sf::RenderWindow* aWindow);
        virtual ~InterfaceLobby();

        virtual void update(float step);
        virtual void draw(sf::RenderWindow* window);
        virtual void handleData(std::string data);

        void sendRdy();
    protected:
        sf::RenderWindow* window;
        sf::Sprite* background;
        std::vector<Button*> buttons;
        float rqtimer;
        float rqtimermax;
};

#endif // INTERFACE_H

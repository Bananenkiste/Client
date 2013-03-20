#ifndef INTERFACEINTRO_H
#define INTERFACESERVERLIST_H

#include "Interface.hpp"

#include <sfml/window.hpp>
#include <sfml/system.hpp>

class Button;

class InterfaceServerlist : public Interface
{
    public:
        InterfaceServerlist(sf::RenderWindow* aWindow);
        virtual ~InterfaceServerlist();

        void update(float step);
        void draw(sf::RenderWindow* window);
    private:
        std::vector<Button*> buttons;

};

#endif // INTERFACEINTRO_H

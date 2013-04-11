#ifndef INTERFACELOADING_HPP
#define INTERFACELOADING_HPP

#include "Interface.hpp"

#include <sfml/window.hpp>
#include <sfml/system.hpp>

class Button;

class InterfaceLoading : public Interface
{
    public:
        InterfaceLoading(sf::RenderWindow* aWindow);
        virtual ~InterfaceLoading();

        void update(float step);
        void draw(sf::RenderWindow* window);
    private:
        std::vector<Button*> buttons;
};

#endif // INTERFACELOADING_HPP

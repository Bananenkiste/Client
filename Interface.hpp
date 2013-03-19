#ifndef INTERFACE_H
#define INTERFACE_H

#include <sfml/window.hpp>
#include <sfml/graphics.hpp>


class Interface
{
    public:
        Interface(sf::RenderWindow* aWindow);
        virtual ~Interface();

        virtual void update(float step);
        virtual void draw(sf::RenderWindow* window);
        virtual void handleData(std::string data);
    protected:
        sf::RenderWindow* window;
        sf::Sprite* background;
};

#endif // INTERFACE_H

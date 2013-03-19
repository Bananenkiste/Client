#ifndef BUTTON_H
#define BUTTON_H

#include "sfml\graphics.hpp"
#include "sfml\window.hpp"

class Button
{
    public:
        Button(std::string title,int x, int y);
        virtual ~Button();
        void update(int x, int y);
        void draw(sf::RenderWindow* win);
        bool getActive();
        std::string getName();
    private:
        bool active;
        std::string name;
        sf::Sprite* normal;
        sf::Sprite* over;
        sf::Text label;
};

#endif // BUTTON_H

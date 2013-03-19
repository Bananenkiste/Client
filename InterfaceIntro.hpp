#ifndef INTERFACEINTRO_H
#define INTERFACEINTRO_H

#include "Interface.hpp"


class Button;

class InterfaceIntro : public Interface
{
    public:
        InterfaceIntro(sf::RenderWindow* aWindow);
        virtual ~InterfaceIntro();

        void update(float step);
        void draw(sf::RenderWindow* window);
    private:
        std::vector<Button*> buttons;

};

#endif // INTERFACEINTRO_H

#ifndef INTERFACEPREGAME_HPP
#define INTERFACEPREGAME_HPP



#include "Interface.hpp"


#include <sfml/window.hpp>
#include <sfml/system.hpp>

class Button;
class Level;

class InterfacePregame : public Interface
{
    public:
        InterfacePregame(sf::RenderWindow* aWindow);
        virtual ~InterfacePregame();


        void setLevel(std::string levelinfo);
        void update(float step);
        void draw(sf::RenderWindow* window);
    protected:
    private:
        std::vector<Button*> buttons;
        Level* level;
};

#endif // INTERFACEPREGAME_HPP

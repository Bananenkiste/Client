#ifndef INTERFACEPREGAME_HPP
#define INTERFACEPREGAME_HPP



#include "Interface.hpp"


#include <sfml/window.hpp>
#include <sfml/system.hpp>

class Bomb;
class Button;
class Level;
class Player;

class InterfacePregame : public Interface
{
    public:
        InterfacePregame(sf::RenderWindow* aWindow);
        virtual ~InterfacePregame();

        void setPlayers(std::vector<Player*>* playerlist);
        void setLevel(std::string levelinfo);
        void update(float step);
        void draw(sf::RenderWindow* window);
        void handleData(std::string);
    protected:
    private:
        std::vector<Button*> buttons;
        Level* level;
        std::vector<Player*>* players;
        std::vector<Bomb*>* bombs;
        int movement;
};

#endif // INTERFACEPREGAME_HPP

#ifndef INTERFACESERVERLIST_H
#define INTERFACESERVERLIST_H

#include "Interface.hpp"

#include <sfml/window.hpp>
#include <sfml/system.hpp>

class Button;
class Server;

class InterfaceServerlist : public Interface
{
    public:
        InterfaceServerlist(sf::RenderWindow* aWindow);
        virtual ~InterfaceServerlist();

        void update(float step);
        void draw(sf::RenderWindow* window);
    private:
        void recieve();
        void sendRequest();

        std::vector<Button*> buttons;
        std::vector<Server*> servers;
        int udp;
        float rqtimer;
        float rqtimermax;
        //bool active;

};

#endif // INTERFACEINTRO_H

#include "InterfaceServerlist.hpp"


#include "Game.hpp"
#include "Network.hpp"
#include "Button.hpp"
#include "Config.hpp"
#include "TextureBuffer.hpp"

InterfaceServerlist::InterfaceServerlist(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("screen",false);
    background->setPosition(0,0);

    buttons.push_back(new Button("Search",Config::getValue("resolution_x")*Config::getValue("serverlist_refreshbutton_x"),Config::getValue("resolution_y")*Config::getValue("serverlist_refreshbutton_y")));

    udp = Network::createUdpSocket();

    sf::Thread udprec (&InterfaceServerlist::recieve,this);
    //udprec.launch();
}

InterfaceServerlist::~InterfaceServerlist()
{
    //dtor
}

void InterfaceServerlist::update(float step)
{
    sf::Vector2i mpos = sf::Mouse::getPosition(*Interface::window);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
        {
            if((*it)->getActive())
            {
                if(strcmp((*it)->getName().c_str(),"Search")==0)
                {
                    std::cout<<"YAY button"<<std::endl;
                    //Game::changeMode(Game::Serverlist);
                    return;
                }
            }
        }
    }
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->update(mpos.x,mpos.y);
    }
}

void InterfaceServerlist::draw(sf::RenderWindow* window)
{
    window->draw(*background);
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->draw(window);
    }
}

void InterfaceServerlist::recieve()
{
    std::cout<<"waiting for incoming Message"<<std::endl;
    std::cout<<Network::recieveData(udp)<<std::endl;
    std::cout<<"recieved Message"<<std::endl;
}

void InterfaceServerlist::sendRequest()
{
    Network::sendData(udp,"BBM|RQSTSRV");
}

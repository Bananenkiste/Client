#include "InterfaceLobby.hpp"
#include "TextureBuffer.hpp"

#include "Game.hpp"
#include "Config.hpp"

InterfaceLobby::InterfaceLobby(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("work",false);
    background->setPosition(0,0);

    //Game::tcpsend("test");
}

InterfaceLobby::~InterfaceLobby()
{
    //dtor
}

void InterfaceLobby::update(float step)
{
    //std::cout<<"yay update"<<std::endl;
}

void InterfaceLobby::draw(sf::RenderWindow* window)
{
    if(background!=NULL)
    {
        //window->draw(*background);
    }
}

void InterfaceLobby::handleData(std::string data)
{

}

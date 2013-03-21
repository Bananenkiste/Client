#include "InterfaceLobby.hpp"
#include "TextureBuffer.hpp"

#include "Game.hpp"

InterfaceLobby::InterfaceLobby(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("work",false);
    background->setPosition(0,0);
    std::cout<<"Lobby"<<std::endl;
}

InterfaceLobby::~InterfaceLobby()
{
    //dtor
}

void InterfaceLobby::update(float step)
{

}

void InterfaceLobby::draw(sf::RenderWindow* window)
{
    window->draw(*background);
}

void InterfaceLobby::handleData(std::string data)
{

}

#include "Interface.hpp"
#include "TextureBuffer.hpp"

Interface::Interface(sf::RenderWindow* aWindow): window(aWindow)
{
    background=TextureBuffer::LoadTexture("work",false);
    background->setPosition(0,0);
}

Interface::~Interface()
{
    //dtor
}

void Interface::update(float step)
{

}

void Interface::draw(sf::RenderWindow* window)
{
    window->draw(*background);
}

void Interface::handleData(std::string data)
{

}

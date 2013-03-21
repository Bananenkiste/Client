#include "Server.hpp"

#include "TextureBuffer.hpp"

Server::Server(std::string aName,std::string aIp,int x, int y):name(aName),ip(aIp)
{
    normal = TextureBuffer::LoadTexture("button",true,x,y);
    over = TextureBuffer::LoadTexture("button_click",true,x,y);
    label.setString(name);
    //label.setFont(TextureBuffer::getFont());
    label.setColor(sf::Color::Cyan);
    label.setPosition(x-normal->getTexture()->getSize().x/2+5,y-label.getCharacterSize()/2);

    active = false;
}

Server::~Server()
{
    //dtor
}

void Server::update(int x, int y)
{
    //check if mouse is over button
    if(normal->getPosition().x+normal->getTexture()->getSize().x/2>x&&
       normal->getPosition().x-normal->getTexture()->getSize().x/2<x&&

       normal->getPosition().y+normal->getTexture()->getSize().y/2>y&&
       normal->getPosition().y-normal->getTexture()->getSize().y/2<y)
    {
        active=true;
    }
    else
    {
        active=false;
    }
}

void Server::draw(sf::RenderWindow* win)
{
    if(active)
    {
        win->draw(*over);
    }
    else
    {
        win->draw(*normal);
    }
    win->draw(label);
}

bool Server::getActive()
{
    return(active);
}
std::string Server::getIp()
{
    return ip;
}

#include "Button.hpp"
#include "TextureBuffer.hpp"

Button::Button(std::string title,int x, int y): name(title)
{
    normal = TextureBuffer::LoadTexture(title,true,x,y);
    over = TextureBuffer::LoadTexture(title+"Click",true,x,y);
    active = false;
}

Button::~Button()
{
    //dtor
}

void Button::update(int x, int y)
{
    //std::cout<<"Mouse: "<<x<<" ="<<    normal->getPosition().x-normal->getTexture()->getSize().x/2<<"-"<<normal->getPosition().x+normal->getTexture()->getSize().x/2<<std::endl;


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

void Button::draw(sf::RenderWindow* win)
{
    if(active)
    {
        win->draw(*over);
    }
    else
    {
        win->draw(*normal);
    }
}

bool Button::getActive()
{
    return(active);
}

std::string Button::getName()
{
    return(name);
}

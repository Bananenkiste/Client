#include "Button.hpp"
#include "TextureBuffer.hpp"

Button::Button(std::string title,int x, int y): name(title)
{
    normal = TextureBuffer::LoadTexture("button",true,x,y);
    over = TextureBuffer::LoadTexture("button_click",true,x,y);
    label.setString(name);
    label.setColor(sf::Color::Cyan);
    label.setPosition(x-normal->getTexture()->getSize().x/2+5,y-label.getCharacterSize()/2);

    active = false;
}

Button::~Button()
{

}

void Button::update(int x, int y)
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
    win->draw(label);
}

bool Button::getActive()
{
    return(active);
}

std::string Button::getName()
{
    return(name);
}

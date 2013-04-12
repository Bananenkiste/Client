#include "Player.hpp"
#include "Network.hpp"
#include "Game.hpp"
#include "Chatwindow.hpp"
#include "TextureBuffer.hpp"

Player::Player(int aid,std::string aname): name(aname), id(aid)
{
    std::stringstream stream;
    stream<<id;
    std::string pawnname= "p"+stream.str();
    std::cout<<"pawn"<<pawnname<<std::endl;
    pawn = TextureBuffer::LoadTexture(pawnname,false);
    playerlabel1 = TextureBuffer::LoadTexture("button",false);
    playerlabel2 = TextureBuffer::LoadTexture("button_click",false);
    label.setString(name);
    label.setColor(sf::Color::Cyan);
    active=false;
}

Player::Player()
{

}

Player::~Player()
{
    //dtor
}

int Player::getId()
{
    return(id);
}

void Player::setSocket(SOCKET asocket)
{
    socket = asocket;
}

std::string Player::getName()
{
    return(name);
}


SOCKET Player::getSocket()
{
    return(socket);
}

void Player::update(float step)
{
    //player update
}

void Player::setActive()
{
    active = !active;
}

void Player::setVariables()
{

}

void Player::draw(sf::RenderWindow* window)
{
    window->draw(*pawn);
}

void Player::drawLabel(sf::RenderWindow* win,float x,float y)
{
    if(!active)
    {
        playerlabel1->setPosition(x,y);
        win->draw(*playerlabel1);
    }
    else
    {
        playerlabel2->setPosition(x,y);
        win->draw(*playerlabel2);
    }

    label.setPosition(playerlabel1->getTexture()->getSize().x/2+5,y+label.getCharacterSize()/2);

    win->draw(label);
}

void Player::setPosition(sf::Vector2f npos)
{
    position=npos;
    pawn->setPosition(npos);
}

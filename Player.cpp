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
    pawn = TextureBuffer::LoadTexture(pawnname,true);
    playerlabel1 = TextureBuffer::LoadTexture("button",false);
    playerlabel2 = TextureBuffer::LoadTexture("button_click",false);
    label.setString(name);
    label.setColor(sf::Color::Cyan);
    active=false;
    dir=0;
    tempdir;
    speed=50;
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
    if(dir!=0)
    {
        sf::Vector2f mov;
        if(dir&1)
        {
            std::cout<<"down"<<std::endl;
            mov-=sf::Vector2f(0,1);
        }
        if(dir&2)
        {
            std::cout<<"up"<<std::endl;
            mov+=sf::Vector2f(0,1);
        }
        if(dir&4)
        {
            std::cout<<"left"<<std::endl;
            mov-=sf::Vector2f(1,0);
        }
        if(dir&8)
        {
            std::cout<<"right"<<std::endl;
            mov+=sf::Vector2f(1,0);
        }
        position.x+=(mov.x*speed)*step;
        position.y+=(mov.y*speed)*step;

        pawn->setPosition(position);
    }
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

void Player::setDir(int ndir)
{
    dir=ndir;
}

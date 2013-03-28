#include "Player.hpp"
#include "Network.hpp"
#include "Game.hpp"
#include "Chatwindow.hpp"

Player::Player(int aid,std::string aname): name(aname), id(aid)
{
    //ctor
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

void Player::setVariables()
{

}

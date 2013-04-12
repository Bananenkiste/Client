#include "InterfacePregame.hpp"

#include "Game.hpp"
#include "Button.hpp"
#include "Config.hpp"
#include "TextureBuffer.hpp"
#include "Level.hpp"
#include "Player.hpp"

InterfacePregame::InterfacePregame(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("intro",false);
    background->setPosition(0,0);
    level=NULL;
    players = Game::getPlayers();
    //buttons.push_back(new Button("Start",Config::getValue("resolution_x")*Config::getValue("intro_startbutton_x"),Config::getValue("resolution_y")*Config::getValue("intro_startbutton_y")));

}

InterfacePregame::~InterfacePregame()
{
    //dtor
}

void InterfacePregame::setLevel(std::string levelinfo)
{
    level = new Level(levelinfo);

    for(std::vector<Player*>::iterator it = players->begin();it!=players->end();++it)
    {
        (*it)->setPosition(level->getSpawn((*it)->getId()));
    }
}

void InterfacePregame::update(float step)
{

    int mov=0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        mov+=1<<0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        mov+=1<<1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        mov+=1<<2;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        mov+=1<<3;
    }
    if(mov!=movement)
    {
        movement=mov;
        std::stringstream stream;
        stream<<mov;
        Game::tcpsend("MOV|"+stream.str());
    }
    /*std::cout<<"Movement"<<mov<<std::endl;
    if(mov&1)
    {
        std::cout<<"down"<<std::endl;
    }
    if(mov&2)
    {
        std::cout<<"up"<<std::endl;
    }
    if(mov&4)
    {
        std::cout<<"left"<<std::endl;
    }
    if(mov&8)
    {
        std::cout<<"right"<<std::endl;
    }*/

}

void InterfacePregame::draw(sf::RenderWindow* window)
{
    if(background!=NULL)
    {
        window->draw(*background);
    }
    if(level!=NULL)
    {
        level->draw(window);
    }
    for(std::vector<Player*>::iterator it = players->begin();it!=players->end();++it)
    {
        (*it)->draw(window);
    }
}

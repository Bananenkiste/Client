#include "InterfacePregame.hpp"

#include "Game.hpp"
#include "Button.hpp"
#include "Config.hpp"
#include "TextureBuffer.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Bomb.hpp"

InterfacePregame::InterfacePregame(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("intro",false);
    background->setPosition(0,0);
    level=NULL;
    players = Game::getPlayers();
    bombs= new std::vector<Bomb*>();
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
    if(players->at(0)->getAlive())
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            mov+=1<<4;
        }
        if(mov!=movement)
        {
            movement=mov;
            std::stringstream stream;
            stream<<mov;
            Game::tcpsend("MOV|"+stream.str());
        }
    }
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
    for(std::vector<Bomb*>::iterator it = bombs->begin();it!=bombs->end();++it)
    {
        (*it)->draw(window);
    }
    for(std::vector<Player*>::iterator it = players->begin();it!=players->end();++it)
    {
        (*it)->draw(window);
    }
}

void InterfacePregame::handleData(std::string data)
{
    std::string key = data.substr(0,data.find_first_of("|"));
    data = data.substr(data.find_first_of("|")+1);
    if(strcmp(key.c_str(),"BOMB")==0)
    {
        if(strcmp(data.substr(0,data.find_first_of("|")).c_str(),"C")==0)
        {
            data = data.substr(data.find_first_of("|")+1);
            std::stringstream stream;
            int x,y;
            stream<<data.substr(0,data.find_first_of(","));
            stream>>x;
            stream.clear();

            stream<<data.substr(data.find_first_of(",")+1);
            stream>>y;

            bombs->push_back(new Bomb(sf::Vector2i(x,y)));
        }
        if(strcmp(data.substr(0,data.find_first_of("|")).c_str(),"R")==0)
        {
            data = data.substr(data.find_first_of("|")+1);
            std::stringstream stream;
            int x,y;
            stream<<data.substr(0,data.find_first_of(","));
            stream>>x;
            stream.clear();
            stream<<data.substr(data.find_first_of(",")+1);
            stream>>y;
            sf::Vector2i pos = sf::Vector2i(x,y);
            for(std::vector<Bomb*>::iterator it = bombs->begin();it!=bombs->end();++it)
            {
                if((*it)->getGridPos()==pos)
                {
                    bombs->erase(it);
                    return;
                }
            }
        }
    }
    if(strcmp(key.c_str(),"EXPL")==0)
    {
        std::stringstream loop;
        loop<<data.substr(0,data.find_first_of("|"));
        int boxes;
        loop>>boxes;
        data = data.substr(data.find_first_of("|")+1);
        for(;boxes>=0;--boxes)
        {
            std::stringstream stream;
            int posx,posy;

            stream<<data.substr(0,data.find_first_of(","));
            stream>>posx;
            stream.clear();

            stream<<data.substr(data.find_first_of(",")+1,data.find_first_of("|"));
            stream>>posy;
            stream.clear();
            level->setTile(posx,posy,0);

            data = data.substr(data.find_first_of("|")+1);
        }

    }
}


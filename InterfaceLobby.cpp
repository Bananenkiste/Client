#include "InterfaceLobby.hpp"
#include "TextureBuffer.hpp"

#include "Game.hpp"
#include "Player.hpp"
#include "Config.hpp"
#include "Button.hpp"

InterfaceLobby::InterfaceLobby(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("work",false);
    background->setPosition(0,0);

    buttons.push_back(new Button("Ready",Config::getValue("resolution_x")*Config::getValue("lobby_readybutton_x"),Config::getValue("resolution_y")*Config::getValue("lobby_readybutton_y")));

    rqtimermax=1;
}

InterfaceLobby::~InterfaceLobby()
{

}

void InterfaceLobby::update(float step)
{
    sf::Vector2i mpos = sf::Mouse::getPosition(*Interface::window);
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->update(mpos.x,mpos.y);
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
        {
            if((*it)->getActive())
            {
                if(strcmp((*it)->getName().c_str(),"Ready")==0)
                {
                    sendRdy();
                    return;
                }
            }
        }
    }
    if(rqtimer>0)
    {
        if(rqtimer<rqtimermax)
        {
           rqtimer+=step;
        }
        else
        {
            rqtimer=0;
        }
    }
}

void InterfaceLobby::draw(sf::RenderWindow* window)
{
    if(background!=NULL)
    {
        window->draw(*background);
    }
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->draw(window);
    }

    std::vector<Player*> temp = Game::getPlayers();
    int c =0;
    for(std::vector<Player*>::iterator it = temp.begin();it!=temp.end();++it)
    {
        int x =50+200*(int)(c/4);
        int y =50+80*(int)(c%4);
        (*it)->drawLabel(window,x,y);
        ++c;
    }


}

void InterfaceLobby::handleData(std::string data)
{

}

void InterfaceLobby::sendRdy()
{
    if(rqtimer==0)
    {
        Game::tcpsend("RDY");
    }
    rqtimer+=0.01f;
}

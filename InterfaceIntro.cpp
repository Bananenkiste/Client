#include "InterfaceIntro.hpp"


#include "Game.hpp"
#include "Button.hpp"
#include "Config.hpp"
#include "TextureBuffer.hpp"

InterfaceIntro::InterfaceIntro(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("work",false);
    background->setPosition(0,0);

    buttons.push_back(new Button("Start",Config::getValue("resolution_x")*Config::getValue("intro_startbutton_x"),Config::getValue("resolution_y")*Config::getValue("intro_startbutton_y")));

}

InterfaceIntro::~InterfaceIntro()
{
    //dtor
}

void InterfaceIntro::update(float step)
{
    sf::Vector2i mpos = sf::Mouse::getPosition(*Interface::window);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
        {
            if((*it)->getActive())
            {
                if(strcmp((*it)->getName().c_str(),"Start")==0)
                {
                    std::cout<<"YAY button"<<std::endl;
                    Game::changeMode(Game::Serverlist);
                    return;
                }
            }
        }
    }
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->update(mpos.x,mpos.y);
    }
}

void InterfaceIntro::draw(sf::RenderWindow* window)
{
    window->draw(*background);
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->draw(window);
    }
}

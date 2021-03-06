#include "InterfaceLoading.hpp"

#include "Game.hpp"
#include "Button.hpp"
#include "Config.hpp"
#include "TextureBuffer.hpp"

InterfaceLoading::InterfaceLoading(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("intro",false);
    background->setPosition(0,0);

    //buttons.push_back(new Button("Start",Config::getValue("resolution_x")*Config::getValue("intro_startbutton_x"),Config::getValue("resolution_y")*Config::getValue("intro_startbutton_y")));

}

InterfaceLoading::~InterfaceLoading()
{
}

void InterfaceLoading::update(float step)
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

void InterfaceLoading::draw(sf::RenderWindow* window)
{
    if(background!=NULL)
    {
        window->draw(*background);
    }
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->draw(window);
    }
}

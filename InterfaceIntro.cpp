#include "InterfaceIntro.hpp"


#include "Game.hpp"
#include "Button.hpp"
#include "Config.hpp"
#include "TextureBuffer.hpp"

InterfaceIntro::InterfaceIntro(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("intro",false);
    background->setPosition(0,0);

    buttons.push_back(new Button("Start",Config::getValue("resolution_x")*Config::getValue("intro_startbutton_x"),Config::getValue("resolution_y")*Config::getValue("intro_startbutton_y")));
    //Loading of all the Textures

    TextureBuffer::LoadTexture("p0",false);
    TextureBuffer::LoadTexture("p1",false);
    TextureBuffer::LoadTexture("p2",false);
    TextureBuffer::LoadTexture("p3",false);
    TextureBuffer::LoadTexture("p4",false);
    TextureBuffer::LoadTexture("p5",false);
    TextureBuffer::LoadTexture("p6",false);
    TextureBuffer::LoadTexture("p7",false);
    TextureBuffer::LoadTexture("0",false);
    TextureBuffer::LoadTexture("1",false);
    TextureBuffer::LoadTexture("2",false);
    TextureBuffer::LoadTexture("bomb",false);
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
                    Game::changeMode(Game::SERVERLIST);
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
    if(background!=NULL)
    {
        window->draw(*background);
    }
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->draw(window);
    }
}

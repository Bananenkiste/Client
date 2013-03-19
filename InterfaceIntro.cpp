#include "InterfaceIntro.hpp"
#include "TextureBuffer.hpp"

#include "Button.hpp"
#include "Config.hpp"

#include <sfml/window.hpp>
#include <sfml/system.hpp>

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

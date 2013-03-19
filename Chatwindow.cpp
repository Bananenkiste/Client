#include "Chatwindow.hpp"
#include "Game.hpp"
#include "Message.hpp"
#include "Network.hpp"
#include "TextureBuffer.hpp"
#include "Config.hpp"


std::vector<Message*> Chatwindow::chat;
sf::Text Chatwindow::text;
bool Chatwindow::active=false;

float Chatwindow::keytime=0.15;
float Chatwindow::responsetime=keytime;

float Chatwindow::spkeytime=0.4;
float Chatwindow::spkeyrtime=spkeytime;


void Chatwindow::update(float step,sf::RenderWindow* window)
{
    sf::Event event;
    if(responsetime<keytime)
    {
        responsetime-=step;
        if(responsetime<0)
        {
            responsetime=keytime;
        }
    }
    if(spkeyrtime<spkeytime)
    {
        spkeyrtime-=step;
        if(spkeyrtime<0)
        {
            spkeyrtime=spkeytime;
        }
    }

    if(!active&&spkeyrtime==spkeytime)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            active=true;
            spkeyrtime-=step;
            text.setCharacterSize(12);
            //text.setFont(*TextureBuffer::getFont());
            text.setStyle(sf::Text::Regular);
            text.setColor(sf::Color::Blue);
            text.setPosition(20,Config::getValue("resolution_y")-20);
        }
    }
    else
    {
        if(active&&responsetime==keytime)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&&spkeyrtime==spkeytime)
            {
                std::string cmp = text.getString();

                if(strcmp(cmp.substr(0,2).c_str(),"c_")==0)
                {
                    Game::console(cmp.substr(2,cmp.length()).c_str());
                    /*std::cout<<"connect befehl"<<std::endl;
                    std::cout<<(cmp.substr(8,cmp.length()).c_str())<<std::endl;
                    Game::connectToServer(cmp.substr(8,cmp.length()).c_str());*/
                }
                else if(strcmp(cmp.c_str(),"")!=0)
                {
                    Game::tcpsend("MSG|"+text.getString());
                }
                text.setString("");
                active=false;
                spkeyrtime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                text.setString(text.getString()+"q");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                text.setString(text.getString()+"w");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                text.setString(text.getString()+"e");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                text.setString(text.getString()+"r");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            {
                text.setString(text.getString()+"t");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                text.setString(text.getString()+"z");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
            {
                text.setString(text.getString()+"u");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            {
                text.setString(text.getString()+"i");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            {
                text.setString(text.getString()+"o");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                text.setString(text.getString()+"p");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                text.setString(text.getString()+"a");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                text.setString(text.getString()+"s");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                text.setString(text.getString()+"d");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                text.setString(text.getString()+"f");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            {
                text.setString(text.getString()+"g");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            {
                text.setString(text.getString()+"h");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            {
                text.setString(text.getString()+"j");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            {
                text.setString(text.getString()+"k");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            {
                text.setString(text.getString()+"l");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
            {
                text.setString(text.getString()+"y");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                text.setString(text.getString()+"x");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                text.setString(text.getString()+"c");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
            {
                text.setString(text.getString()+"v");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            {
                text.setString(text.getString()+"b");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
            {
                text.setString(text.getString()+"n");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                text.setString(text.getString()+"m");
                responsetime-=step;
            }
            //num key
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
            {
                text.setString(text.getString()+"0");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                text.setString(text.getString()+"1");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                text.setString(text.getString()+"2");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                text.setString(text.getString()+"3");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                text.setString(text.getString()+"4");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
            {
                text.setString(text.getString()+"5");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
            {
                text.setString(text.getString()+"6");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
            {
                text.setString(text.getString()+"7");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
            {
                text.setString(text.getString()+"8");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
            {
                text.setString(text.getString()+"9");
                responsetime-=step;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Back))
            {
                std::string ntext = text.getString();
                if(ntext.size()>0)
                {
                    ntext.resize(ntext.size()-1);
                    text.setString(ntext);
                }
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                text.setString(text.getString()+" ");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
            {
                text.setString(text.getString()+".");
                responsetime-=step;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
            {
                text.setString(text.getString()+"_");
                responsetime-=step;
            }
        }
    }
}

void Chatwindow::draw(sf::RenderWindow* window)
{
    for(std::vector<Message*>::iterator it = chat.begin();it!=chat.end();++it)
    {
        (*it)->draw(window);
    }
    if(active)
    {
        window->draw(text);
    }
}

void Chatwindow::addText(std::string msg)
{
    chat.insert(chat.begin(),new Message(msg));
    if(chat.size()>10)
    {
        chat.resize(10);
    }
    for(int x=0;x<chat.size();++x)
    {
        chat[x]->setPosition(20,Config::getValue("resolution_y")-40-(20*x));
    }
}

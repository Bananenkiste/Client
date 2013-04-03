#include "InterfaceServerlist.hpp"


#include "Game.hpp"
#include "Network.hpp"
#include "Button.hpp"
#include "Config.hpp"
#include "Server.hpp"
#include "TextureBuffer.hpp"


InterfaceServerlist::InterfaceServerlist(sf::RenderWindow* aWindow): Interface(aWindow)
{
    background=TextureBuffer::LoadTexture("screen",false);
    background->setPosition(0,0);

    buttons.push_back(new Button("Search",Config::getValue("resolution_x")*Config::getValue("serverlist_refreshbutton_x"),Config::getValue("resolution_y")*Config::getValue("serverlist_refreshbutton_y")));

    udp = Network::createUdpSocket();
    Network::bindSocket(udp);

    sf::Thread* udprec= new sf::Thread(&InterfaceServerlist::recieve,this);
    udprec->launch();
    rqtimermax=1;
    return;
}

InterfaceServerlist::~InterfaceServerlist()
{
    //dtor
}

void InterfaceServerlist::update(float step)
{
    sf::Vector2i mpos = sf::Mouse::getPosition(*Interface::window);
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
        {
            if((*it)->getActive())
            {
                if(strcmp((*it)->getName().c_str(),"Search")==0)
                {
                    sendRequest();
                    return;
                }
            }
        }
        for(std::vector<Server*>::iterator it=servers.begin();it!=servers.end();++it)
        {
            if((*it)->getActive())
            {
                Game::connectToServer((*it)->getIp());
            }
        }
    }
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->update(mpos.x,mpos.y);
    }
    for(std::vector<Server*>::iterator it=servers.begin();it!=servers.end();++it)
    {
        (*it)->update(mpos.x,mpos.y);
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

void InterfaceServerlist::draw(sf::RenderWindow* window)
{
    if(background)
    {
       //window->draw(*background);
    }
    for(std::vector<Button*>::iterator it=buttons.begin();it!=buttons.end();++it)
    {
        (*it)->draw(window);
    }
    for(std::vector<Server*>::iterator it2=servers.begin();it2!=servers.end();++it2)
    {
        (*it2)->draw(window);
    }
}

void InterfaceServerlist::recieve()
{
    while(true)
    {
        std::string msg = Network::recieveData(udp);
        std::string key = msg.substr(0,msg.find_first_of("|"));
        msg = msg.substr(msg.find_first_of("|")+1);

        if(strcmp(key.c_str(),"BBM")==0)
        {
            if(strcmp(msg.substr(0,msg.find_first_of("|")).c_str(),"SRV")==0)
            {
                msg = msg.substr(msg.find_first_of("|")+1);
                std::string name = msg.substr(0,msg.find_first_of("|"));
                name.resize(8);
                std::string ip = msg.substr(msg.find_first_of("|")+1);
                std::cout<<"msg:"<<name<<"key:"<<ip<<std::endl;
                bool n=true;
                for(std::vector<Server*>::iterator it = servers.begin();it!=servers.end();++it)
                {
                    if(strcmp((*it)->getIp().c_str(),ip.c_str())==0)
                    {
                        n=false;
                    }
                }
                if(n)
                {
                    int x =20+200*(int)(servers.size()/4);
                    int y =200+80*(int)(servers.size()%4);
                    servers.push_back(new Server(name,ip,100+x,y));
                }
            }
        }
    }
}

void InterfaceServerlist::sendRequest()
{
    if(rqtimer==0)
    {
        Network::broadcastSend(udp,40001,"BBM|RQSRV");
    }
    rqtimer+=0.01f;

}

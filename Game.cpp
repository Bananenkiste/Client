#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <sstream>

#include "Config.hpp"
#include "Game.hpp"
#include "Time.hpp"
#include "Network.hpp"
#include "Player.hpp"
#include "Chatwindow.hpp"

#include "Interface.hpp"
#include "InterfaceIntro.hpp"
//#include "InterfaceMenu.hpp"
//#include "InterfaceLobby.hpp"
//#include "InterfaceServerlist.hpp"
#include "TextureBuffer.hpp"

std::vector<Player*> Game::players;
bool Game::end;
sf::RenderWindow* Game::window;
int Game::state;
Interface* Game::ui;
int Game::tcpsocket;


void Game::run()
{
    while(end != true)
    {
        Time::update();
		windowControl();
        ui->update(Time::step());
        switch(state)
        {
            case Game::Lobby:
            {
                Game::tcpcheck();
                for(std::vector<Player*>::iterator it=players.begin();it!=players.end();++it)
                {
                    (*it)->update(Time::step());
                }
                break;
            }
        }
		Chatwindow::update(Time::step(),window);
        Game::draw();
    }
    Network::closeSocket(tcpsocket);
    free(ui);
    WSACleanup();
    return;
}

void Game::changeMode(int newMode)
{
    switch(newMode)
    {
        case Game::Intro :
        {
            ui = (Interface*) new InterfaceIntro(window);
            break;
        }
        case Game::Menu :
        {
            //ui = (Interface*) new InterfaceMenu(window);
            break;
        }
        case Game::Lobby :
        {

            //ui = (Interface*) new InterfaceLobby(window);
            break;
        }
        case Game::Ingame :
        {
            //ui = (Interface*) new InterfaceMenu(window);
            break;
        }
        case Game::Debrief :
        {
            //ui = (Interface*) new InterfaceMenu(window);
            break;
        }
        case Game::Settings :
        {
            //ui = (Interface*) new InterfaceMenu(window);
            break;
        }
        case Game::Serverlist :
        {
            //ui = (Interface*) new InterfaceServerlist(window);
            break;
        }
        default:
        {
            return;
        }

    }
    state = newMode;
}

void Game::windowControl()
{
    sf::Event event;
	while (window->pollEvent(event))
	{
		if ( event.type == sf::Event::Closed )
		{
			end=true;
		}
	}
}

void Game::draw()
{
    window->clear();
    window->pushGLStates();

    ui->draw(window);
    Chatwindow::draw(window);

    window->popGLStates();
    window->display();
}


void Game::init()
{
    /////////////////////////////////////////////////
    ///////////////////  Networkstart  //////////////
    /////////////////////////////////////////////////
    WSADATA w;
    if(int result = WSAStartup(MAKEWORD(2,2), &w) != 0)
    {
        std::cout << "Winsock 2 konnte nicht gestartet werden! Error #" << result << std::endl;
        return;
    }
    /////////////////////////////////////////////////
    /////////////////  Startup window  //////////////
    /////////////////////////////////////////////////
    Config::load();
    state = Game::Intro;
    createWindow(Config::getValue("resolution_x"),Config::getValue("resolution_y"));
    //TextureBuffer::loadFont(Config::getString("font"));
    end = false;

    std::string aname = "Player";
    tcpsocket = Network::createSocket();

    run();
}

void Game::createWindow(int x,int y)
{
    window = new sf::RenderWindow(sf::VideoMode(x,y,sf::VideoMode::getDesktopMode().bitsPerPixel), "Bomberman - Client");
    window->setVerticalSyncEnabled(true);
    changeMode(state);
}

void Game::connectToServer(std::string Ip)
{
    int i=0;
    while(Network::connectTo(tcpsocket,Ip,40000)!=1)
    {
        i++;
        Chatwindow::addText("Could not connect to Server");
        std::cout<<"Networkfailure Try: "<<i<<std::endl;
        if(i==10)
        {
            Game::changeMode(Game::Serverlist);
        }
    }
    Network::sendData(tcpsocket,"IDENT|"+Config::getString("name"));
    Game::changeMode(Game::Lobby);
    std::cout<<"Connected"<<std::endl;
}

void Game::dataInterface(std::string data)
{
    ui->handleData(data);
}

void Game::console(std::string cmp)
{
    if(strcmp(cmp.substr(1,8).c_str(),"connect")==0)
    {
        std::cout<<"connect befehl"<<std::endl;
        std::cout<<(cmp.substr(8,cmp.length()).c_str())<<std::endl;
        Game::connectToServer(cmp.substr(8,cmp.length()).c_str());
    }
    else if(strcmp(cmp.c_str(),"ip")==0)
    {
        Chatwindow::addText(Network::getIP().c_str());
    }
}

void Game::tcpcheck()
{
    if(tcpsocket!= INVALID_SOCKET)
    {
        std::string msg = Network::recieveData(tcpsocket);
        if(strcmp("",msg.c_str())!=0)
        {
            std::string key = msg.substr(0,msg.find_first_of("|"));
            msg = msg.substr(msg.find_first_of("|")+1);
            if(strcmp("CLOSE",key.c_str())==0)
            {
                std::string nmsg = "Server down!";
                Chatwindow::addText(nmsg);
                closesocket(tcpsocket);
                tcpsocket = INVALID_SOCKET;
                Game::changeMode(Game::Serverlist);
                return;
            }
            if(strcmp("MSG",key.c_str())==0)
            {
                Chatwindow::addText(msg.substr(msg.find_first_of("|")+1));
            }
            if(strcmp("PJOIN",key.c_str())==0)
            {
                std::stringstream stream;
                stream<<msg.substr(0,msg.find_first_of("|"));
                int id;
                stream>>id;

                msg = msg.substr(msg.find_first_of("|")+1);
                std::string name = msg.substr(0,msg.find_first_of("|"));

                players.push_back(new Player(id,name));
                std::cout<<"ID:"<<id<<"Name:"<<name<<std::endl;
            }
            if(strcmp("PLEAVE",key.c_str())==0)
            {

                for(std::vector<Player*>::iterator it = players.begin();it!=players.end();++it)
                {
                    std::stringstream stream;
                    stream<<msg.substr(0,msg.find_first_of("|"));
                    int delid;
                    stream>>delid;
                    if((*it)->getId()==delid)
                    {
                        Chatwindow::addText((*it)->getName()+" left the game.");
                        players.erase(it);
                    }
                }

            }
            if(strcmp("PACT",key.c_str())==0)
            {
                std::stringstream stream;
                stream<<msg.substr(0,msg.find_first_of("|"));
                int id;
                stream>>id;
            }
        }
    }
}

void Game::tcpsend(std::string data)
{
    Network::sendData(tcpsocket,data);
}

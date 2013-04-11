#ifndef GAME_H
#define GAME_H

#include <sfml/window.hpp>
#include <sfml/graphics.hpp>
#include <sfml/system.hpp>
#include <vector>

#include "Player.hpp"

class Interface;

class Game
{
    public:
        enum State{INTRO,LOGIN,MENU,SERVERLIST,LOBBY,LOADING,PREGAME,INGAME,DEBRIEF,SETTINGS};

        static void init();
        static void run();
        static void draw();
        static void createWindow(int x, int y);
        static void changeMode(int newMode);
        static void connectToServer(std::string Ip);
        static void dataInterface(std::string data);
        static void console(std::string cmp);
        static void tcpcheck();
        static void tcpsend(std::string data);
        static std::vector<Player*> getPlayers();



    private:
		static void windowControl();
        static sf::RenderWindow* window;
        static std::vector<Player*> players;
        static bool end;
        static int state;
        static Interface* ui;
        static int tcpsocket;
        static sf::Thread tcp;
};

#endif // GAME_H

#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <winsock2.h>
#include <windows.h>
//libws2_32.a einbinden

class Network
{
    public:
        static void init();
        static SOCKET createSocket();

        static int connectTo(SOCKET Socket,std::string ip,int port);
        static SOCKET waitForConnection(SOCKET node);
        static void WaitForClient(SOCKET node, SOCKET s);

        static void sendData(SOCKET node,std::string msg);
        static std::string recieveData(SOCKET node);

        static void closeSocket(SOCKET node);
        static std::string getIP();

    protected:
    private:
        static bool i;
        static FD_SET fdset;
};

#endif // SOCKET_H

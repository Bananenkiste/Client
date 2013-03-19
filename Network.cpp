#include "Network.hpp"


//Global Variables
bool Network::i;
FD_SET Network::fdset;


void Network::init()
{
    WSADATA w;
    if(int result = WSAStartup(MAKEWORD(2,2), &w) != 0)
    {
        std::cout << "Winsock 2 konnte nicht gestartet werden! Error #" << result << std::endl;
        return;
    }
    i=true;
}
SOCKET Network::createSocket()
{
    if(!i)
    {
        init();
    }
    int node = socket(AF_INET, SOCK_STREAM, 0);
    if(node == INVALID_SOCKET)
    {
        std::cout << "Socket konnte nicht erstellt werden!" << std::endl;
        return NULL;
    }
    std::cout << "Socket konnte erstellt werden!" << std::endl;
    return node;
}

int Network::connectTo(SOCKET Socket,std::string ip,int port)
{
    sockaddr_in service;             // Normale IPv4 Struktur
    service.sin_family = AF_INET;   // AF_INET f�r IPv4, f�r IPv6 w�re es AF_INET6
    service.sin_port = htons(port);
    service.sin_addr.s_addr = inet_addr(ip.c_str());

    int result = connect(Socket, reinterpret_cast<sockaddr*>(&service), sizeof(service));
    if(result == -1)
    {
        std::cout << "Verbindung fehlgeschlagen!" <<WSAGetLastError()<< std::endl;
        return -1;
    }
    return 1;
    /*char buffer[256];
    strcpy(buffer,"hello you");
    send(Socket,buffer,strlen(buffer),0);
    std::cout << "Verbindung erfolgreich!" << std::endl;
    closesocket(Socket);
    */
}

SOCKET Network::waitForConnection(SOCKET node)
{
    sockaddr_in addr;             // Normale IPv4 Struktur
    addr.sin_family = AF_INET;   // AF_INET f�r IPv4, f�r IPv6 w�re es AF_INET6
    addr.sin_port = htons(40000);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind( node, (SOCKADDR*) &addr, sizeof(addr) ) != SOCKET_ERROR )
    {
        if(listen(node,SOMAXCONN)!=SOCKET_ERROR)
        {
            do
            {
                std::cout<<"Listen...."<<std::endl;
                SOCKET s;
                s = accept( node, NULL, NULL );
                closesocket(node);
                return s;

                /*std::cout<<"Wait for data"<<std::endl;
                char buffer[256];
                int rc;
                rc=recv(s,buffer,256,0);
                buffer[rc]=0;
                std::cout<<"Message from client:"<<buffer<<std::endl;*/

            }
            while(1);




        }
        else
        {
            std::cout<<"nope:"<<WSAGetLastError()<<std::endl;
        }
    }
    else
    {
        std::cout<<"asdf:"<<WSAGetLastError()<<std::endl;
    }
}

void Network::WaitForClient(SOCKET node, SOCKET s)
{
    s = accept( node, NULL, NULL );
    if(s!=INVALID_SOCKET)
    {
        std::cout<<"no error"<<std::endl;
    }
    else
    {
        std::cout<<"error"<<std::endl;
    }
}

void Network::sendData(SOCKET node,std::string msg)
{
    //char buffer[256];
    //strcpy(buffer,"hello you");
    send(node,msg.c_str(),strlen(msg.c_str()),0);
}

std::string Network::recieveData(SOCKET node)
{
    float rc;
    FD_ZERO(&Network::fdset);
    FD_SET(node,&Network::fdset);
    struct timeval timeout;
    timeout.tv_sec=0.01;
    timeout.tv_usec=0;

    rc=select(0,&Network::fdset,NULL,NULL,&timeout);
    //std::cout<<"RC: "<<rc<<std::endl;
    if(rc==SOCKET_ERROR)
    {
      //printf("Fehler: select, fehler code: %s\n",WSAGetLastError());
      return("CLOSE");
    }

    if(FD_ISSET(node,&Network::fdset))
    {
        char buffer[256];
        int rc;
        rc=recv(node,buffer,256,0);
        buffer[rc]=0;
        //std::cout<<"Message from client:"<<buffer<<std::endl;
        std::string msg = buffer;
        return msg;
    }
    return("");
}

void Network::closeSocket(SOCKET node)
{
    sendData(node,"CLOSE");
    closesocket(node);
}

std::string Network::getIP()
{

}

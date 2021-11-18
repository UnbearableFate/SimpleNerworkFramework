#pragma once
#include"Acceptor.h"
#include"EventLoop.h"
#include<iostream>
#include<map>
#include"TcpConnection.h"
class TcpServer
{
private:
	Acceptor acceptor;
	EventLoop entranceLoop;
	std::function<void(char*)> messageHandle;
	std::map<int, std::shared_ptr<TcpConnection>> tcpConnMap;
	TcpServer(TcpServer&) = delete;
	TcpServer& operator=(TcpServer&) = delete;
public:
	TcpServer(int port, std::function<void(void)> func);
	~TcpServer();
	void start();
	void createNewConn(int connfd, sockaddr_in cliAddr);
	
};


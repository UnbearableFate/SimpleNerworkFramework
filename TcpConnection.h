#pragma once
#include<sys/socket.h>
#include<netinet/in.h>
#include"Channel.h"
#include<vector>
#include<stdio.h>
#include<unistd.h>
class TcpConnection
{
private:
	sockaddr_in servAddr;
	sockaddr_in	cliAddr;
	Channel tcpConnChan;
	std::vector<char> sendBuffer;
	std::vector<char> receiveBuffer;
	void readFromConn();
	void writeToConn();
	std::function<void(char*)> messageHandleCallback;
public:
	TcpConnection(int cfd, sockaddr_in cAddr);
	Channel* getChanPtr() { return &tcpConnChan; }
};


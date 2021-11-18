#pragma once
#include<sys/socket.h>
#include<netinet/in.h>
#include"Channel.h"
#include<vector>
#include<stdio.h>
#include<unistd.h>
#include<memory>
#include<functional>

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
private:
	sockaddr_in servAddr;
	sockaddr_in	cliAddr;
	Channel tcpConnChan;
	std::vector<char> sendBuffer;
	std::vector<char> receiveBuffer;
	void readFromConn();
	void writeToConn();
	std::function<void(std::vector<char>&)> messageHandleCallback;
	//std::function<void(const std::shared_ptr<TcpConnection>&,std::vector<char>&)> messageHandleCallback;
public:
	TcpConnection(int cfd, sockaddr_in cAddr);
	void send(std::vector<char>&);
	using TcpConnPtr = const std::shared_ptr<TcpConnection>&;
	using Buff = std::vector<char>&;
	using MessageHandleFunc = std::function<void(TcpConnPtr, Buff)>;
	Channel* getChanPtr() { return &tcpConnChan; }
	void setMessageHandleCallback(MessageHandleFunc func) {
		messageHandleCallback = std::bind(func,shared_from_this(),std::placeholders::_1);
	};
};


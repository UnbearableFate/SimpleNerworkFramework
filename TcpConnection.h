#pragma once
#include<sys/socket.h>
#include<netinet/in.h>
#include"Channel.h"
#include<vector>
#include<stdio.h>
#include<unistd.h>
#include<memory>
#include<functional>
#include"WriteBuffer.h"
#include"Buffer.h"

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
private:
	sockaddr_in servAddr;
	sockaddr_in	cliAddr;
	Channel tcpConnChan;
	WriteBuffer sendBuffer;
	Buffer receiveBuffer;
	void readFromConn();
	void writeToConn();
	std::function<void(Buffer)> messageHandleCallback;
	std::function<void(void)> closeCallback;
public:
	TcpConnection(int cfd, sockaddr_in cAddr);
	~TcpConnection();
	void send(std::vector<char>&);
	using TcpConnPtr = const std::shared_ptr<TcpConnection>&;
	using MessageHandleFunc = std::function<void(TcpConnPtr, Buffer)>;
	Channel* getChanPtr() { return &tcpConnChan; }
	void setMessageHandleCallback(MessageHandleFunc func) {
		messageHandleCallback = std::bind(func,shared_from_this(),std::placeholders::_1);
	};
	void setCloseCallback(const std::function<void(void)>& cb) { closeCallback = cb; };
	void CloseConn();
	std::string getCliAddrStr();
};


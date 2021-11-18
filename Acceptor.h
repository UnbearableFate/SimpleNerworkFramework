#pragma once
#include<sys/socket.h>
#include<netinet/in.h>

#include"Channel.h"
#include<memory>
#include"EventLoop.h"
class Acceptor
{
private:
	int sockfd;
	sockaddr_in servAddr;
	Channel acceptChan;
	std::function<void(int, sockaddr_in)> createNewConnCallback;
public:
	Acceptor(int);
	void acceptWhenReady();
	Channel* getChannelPtr() { return &acceptChan; }
	void setCreateNewConnCallback(std::function<void(int, sockaddr_in)> func) { createNewConnCallback = std::move(func); }
};


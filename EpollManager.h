#pragma once
#include<vector>
#include<sys/epoll.h>
#include<unistd.h>
#include "Channel.h"
#include<map>
#include<memory>
#include <string.h>  // memset
class EpollManager
{
private:
	int eventFd;
	std::vector<epoll_event> eventsVector;
	std::map<int, Channel*> registeredChannelMap;
public:
	EpollManager();
	~EpollManager();

	void addEvent(Channel*);
	void modifyEvent(Channel*);
	void deleteEvent(Channel*);
	std::vector<Channel*> pollWait();
};


#pragma once
#include<vector>
#include"Channel.h"
#include"EpollManager.h"
#include<memory>
#include<iostream>
#include<vector>
#include<functional>
#include <sys/eventfd.h>
class EventLoop
{
private:
	//std::vector<Channel*> channels;
	Channel notifiChannel;
	std::shared_ptr<EpollManager> epollMgr;
	std::vector<std::function<void(void)>> pendingFuncList;
	EventLoop(EventLoop&) = delete;
	EventLoop& operator=(const EventLoop&) = delete;
public:
	void loop();
	bool isLooping;
	EventLoop();
	void addOverseeChannel(Channel *chan);
	void addPendingFunc(std::function<void(void)>);
	void removeChannel(Channel* chan);
};


#pragma once
#include<vector>
#include"Channel.h"
#include"EpollManager.h"
#include<memory>
#include<iostream>
class EventLoop
{
private:
	std::vector<Channel*> channels;
	std::shared_ptr<EpollManager> epollMgr;
	EventLoop(EventLoop&) = delete;
	EventLoop& operator=(const EventLoop&) = delete;
public:
	void loop();
	EventLoop();
	void addOverseeChannel(Channel *chan);
};


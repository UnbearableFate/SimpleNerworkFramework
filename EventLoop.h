#pragma once
#include<vector>
#include"Channel.h"
#include"EpollManager.h"
#include<memory>
#include<iostream>
#include<vector>
#include<functional>
#include <sys/eventfd.h>
#include<thread>
#include<mutex>
#include<condition_variable>
class EventLoop
{
private:
	//std::vector<Channel*> channels;
	Channel notifiChannel;
	bool used = false;
	std::shared_ptr<EpollManager> epollMgr;
	std::vector<std::function<void(void)>> pendingFuncList;
	EventLoop(EventLoop&) = delete;
	EventLoop& operator=(const EventLoop&) = delete;
	std::thread t;
	std::mutex mut;
	std::condition_variable cv;

public:
	void loop();
	void loopInThread();
	void mainLoopThread();
	bool isLooping;
	EventLoop();
	void addOverseeChannel(Channel *chan);
	void addPendingFunc(std::function<void(void)>);
	void removeChannel(Channel* chan);
	void startLoop();
};


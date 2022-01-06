#pragma once
#include "EventLoop.h"
#include <mutex>
#include <thread>
#include <condition_variable>
class EventLoopThread
{
private:
	std::mutex mtx;
	EventLoop* loop;
	std::thread thr;
	std::condition_variable cv;
	std::function<void(EventLoop*)> initCallback;

public:


};


#include "EventLoop.h"
#include <iostream>
EventLoop::EventLoop():epollMgr(std::make_shared<EpollManager>()),notifiChannel(eventfd(0, EFD_CLOEXEC|EFD_NONBLOCK),this) {
	isLooping = false;
	this->addOverseeChannel(&notifiChannel);
	notifiChannel.setReadCallback([&]() {
		uint64_t one = 1;
		ssize_t n = read(notifiChannel.getFd(), &one, sizeof one);
		if (n != sizeof one)
		{
			std::cout << "xixi" << std::endl;
		}
	});
}

void EventLoop::loop() {
	while (true)
	{
		{
			std::unique_lock<std::mutex> lock(mut);
			while (!isLooping)
			{
				cv.wait(lock);
			}
		}
		auto activeChannels = epollMgr->pollWait();
		for(auto ch : activeChannels) {
			ch->handleIO();
		}
		for (auto func : pendingFuncList) {
			func();
		}
		pendingFuncList.clear();
	}
}

void EventLoop::addOverseeChannel(Channel *chan) {
	chan->setOwnerLoop(this);
	this->epollMgr->addEvent(chan);
}

void EventLoop::addPendingFunc(std::function<void(void)> func) {
	if (pendingFuncList.empty()) {
		char noti = '0';
		write(notifiChannel.getFd(), &noti, 1);
	}
	pendingFuncList.push_back(func);
}

void EventLoop::removeChannel(Channel* chan) {
	this->epollMgr->deleteEvent(chan);
}

void EventLoop::loopInThread() {
	t = std::thread(std::bind(&EventLoop::loop,this));
	t.detach();
}

void EventLoop::startLoop() {
	isLooping = true;
	cv.notify_all();
}

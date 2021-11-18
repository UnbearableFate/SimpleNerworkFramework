#include "EventLoop.h"

EventLoop::EventLoop():epollMgr(std::make_shared<EpollManager>()) {
	;
}

void EventLoop::loop() {
	while (true)
	{
		auto activeChannels = epollMgr->pollWait();
		for(auto ch : activeChannels) {
			ch->handleIO();
			std::cout << "gogogo" << std::endl;
		}
	}
}

void EventLoop::addOverseeChannel(Channel *chan) {
	this->epollMgr->addEvent(chan);
}

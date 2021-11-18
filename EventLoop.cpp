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
		}
	}
}

void EventLoop::addOverseeChannel(Channel *chan) {
	this->epollMgr->addEvent(chan);
}

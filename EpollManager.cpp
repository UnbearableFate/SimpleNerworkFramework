#include "EpollManager.h"

EpollManager::EpollManager():eventsVector(16){
	eventFd = epoll_create1(EPOLL_CLOEXEC);
}

EpollManager::~EpollManager() {
	close(eventFd);
}

void EpollManager::addEvent(Channel *channel) {
	epoll_event e;
	memset(&e, 0, sizeof(e));
	e.data.ptr = channel;
	e.events = channel->getEvent();
	int fd = channel->getFd();
	epoll_ctl(eventFd, EPOLL_CTL_ADD, channel->getFd(),&e);
	this->registeredChannelMap[fd] = channel;
}
/*
void EpollManager::modifyEvent(Channel& channel) {
	epoll_event e;
	e.data.ptr = &channel;
	e.events = channel.getEvent();
	epoll_ctl(eventFd, EPOLL_CTL_ADD, channel.getFd(), &e);
}
*/

 std::vector<Channel*> EpollManager::pollWait() {
	int num = epoll_wait(this->eventFd, &*this->eventsVector.begin(), static_cast<int>( eventsVector.size()), -1);
	std::vector<Channel*> activeChennel;
	for (int i = 0; i != num; ++i) {
		auto ch = static_cast<Channel*> (eventsVector[i].data.ptr);
		ch->rEvent = eventsVector[i].events;
		activeChennel.push_back(ch);
	}
	return activeChennel;
}

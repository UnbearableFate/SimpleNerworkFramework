#pragma once
#include<sys/epoll.h>
#include<functional>
class Channel {
private:
	friend class EpollManager;
	const int fd;
	int event;
	int rEvent;
	//EpollManager* ownerMgr;
	std::function<void(void)> readCallback;
	std::function<void(void)> writeCallback;
	std::function<void(void)> errorCallback;
	
public:
	static const int READ_EVE = EPOLLIN | EPOLLPRI;
	static const int WRITE_EVE = EPOLLOUT;
	std::function<void(void)> update;
	Channel() : fd(-1),readCallback(nullptr),writeCallback(nullptr),errorCallback(nullptr) {}
	Channel(int f) :fd(f), event(0),readCallback(nullptr), writeCallback(nullptr), errorCallback(nullptr) {}
	int getFd() const { return fd; }
	int getEvent() const { return event; }
	void handleIO();
	void enableEvent(int e) { event |= e; }
	void disableEvent(int e) { event &= ~e; }
	void setReadCallback(const std::function<void(void)> func) { readCallback = std::move(func); }
	void setWriteCallback(std::function<void(void)> func) { writeCallback = std::move(func); }
	void setErrorCallback(std::function<void(void)> func) { errorCallback = std::move(func); }
};


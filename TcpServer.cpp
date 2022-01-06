#include "TcpServer.h"
#include <iostream>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <thread>

TcpServer::TcpServer(int port,TcpConnection::MessageHandleFunc func):entranceLoop(), acceptor(Acceptor(port)),eventLoopPool(3) {
	this->entranceLoop.addOverseeChannel(acceptor.getChannelPtr());
	this->acceptor.setCreateNewConnCallback(std::bind(&TcpServer::createNewConn, this, std::placeholders::_1,
		std::placeholders::_2, func));
	for (int i = 0; i != eventLoopPool.size(); ++i) {
		eventLoopPool[i].loopInThread();
	}
}

void TcpServer::createNewConn(int connfd, sockaddr_in cliAddr,TcpConnection::MessageHandleFunc func) {
	this->tcpConnMap[connfd] = std::make_shared<TcpConnection>(connfd, cliAddr);
	this->tcpConnMap[connfd]->setMessageHandleCallback(func);
	auto usefulLoop = this->getNextLoop();
	usefulLoop->addOverseeChannel(tcpConnMap[connfd]->getChanPtr());
	this->tcpConnMap[connfd]->setCloseCallback(std::bind(&TcpServer::closeConn, this, connfd));
	char ip[20];
	inet_ntop(AF_INET, (sockaddr*)&cliAddr, ip, sizeof(cliAddr));
	printf("Connected from %s\n", ip);
	usefulLoop->startLoop();
}

void TcpServer::start() {
	entranceLoop.isLooping = true;
	entranceLoop.loop();
}

void TcpServer::closeConn(int connfd) {
	tcpConnMap[connfd]->CloseConn();
	tcpConnMap[connfd]->setMessageHandleCallback(nullptr);
	std::cout << "byebye" << tcpConnMap[connfd]->getCliAddrStr() << std::endl;
	std::cout << tcpConnMap[connfd].use_count() << std::endl;
	tcpConnMap.erase(connfd);
	std::cout << "byebye" << std::endl;
}

TcpServer::~TcpServer() {
	tcpConnMap.clear();
}

EventLoop* TcpServer::getNextLoop() {
	for (int i = 0; i != eventLoopPool.size(); ++i) {
		if (!eventLoopPool[i].isLooping) {
			eventLoopPool[i].isLooping = true;
			return &eventLoopPool[i];
		}
	}
	return nullptr;
}

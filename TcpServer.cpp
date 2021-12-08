#include "TcpServer.h"
#include <iostream>
#include <arpa/inet.h>
#include <string>
#include <iostream>

TcpServer::TcpServer(int port,TcpConnection::MessageHandleFunc func):entranceLoop(), acceptor(Acceptor(port)) {
	this->entranceLoop.addOverseeChannel(acceptor.getChannelPtr());
	this->acceptor.setCreateNewConnCallback(std::bind(&TcpServer::createNewConn, this, std::placeholders::_1,
		std::placeholders::_2, func));
}

void TcpServer::createNewConn(int connfd, sockaddr_in cliAddr,TcpConnection::MessageHandleFunc func) {
	this->tcpConnMap[connfd] = std::make_shared<TcpConnection>(connfd, cliAddr);
	std::cout << tcpConnMap[connfd].use_count() << std::endl;

	this->tcpConnMap[connfd]->setMessageHandleCallback(func);
	std::cout << tcpConnMap[connfd].use_count() << std::endl;

	this->entranceLoop.addOverseeChannel(tcpConnMap[connfd]->getChanPtr());

	this->tcpConnMap[connfd]->setCloseCallback(std::bind(&TcpServer::closeConn, this, connfd));
	std::cout << tcpConnMap[connfd].use_count() << std::endl;

	char ip[20];
	inet_ntop(AF_INET, (sockaddr*)&cliAddr, ip, sizeof(cliAddr));
	printf("Connected from %s\n", ip);
}

void TcpServer::closeConn(int connfd) {
	tcpConnMap[connfd]->CloseConn();
	tcpConnMap[connfd]->setMessageHandleCallback(nullptr);
	std::cout << "byebye" << tcpConnMap[connfd]->getCliAddrStr() << std::endl;
	std::cout << tcpConnMap[connfd].use_count() << std::endl;
	tcpConnMap.erase(connfd);
	std::cout << "byebye" << std::endl;
}

void TcpServer::start() {
	entranceLoop.isLooping = true;
	entranceLoop.loop();
}

TcpServer::~TcpServer() {
	tcpConnMap.clear();
}

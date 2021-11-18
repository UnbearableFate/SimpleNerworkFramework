#include "TcpServer.h"

TcpServer::TcpServer(int port, std::function<void(void)> func): acceptor(Acceptor(port)) {
	this->entranceLoop = EventLoop();
	this->entranceLoop.addOverseeChannel(acceptor.getChannelPtr());
	this->acceptor.setCreateNewConnCallback(std::bind(&TcpServer::createNewConn, this, std::placeholders::_1, std::placeholders::_2));
}

void TcpServer::createNewConn(int connfd, sockaddr_in cliAddr) {
	auto newConn =  std::make_shared<TcpConnection>(connfd, cliAddr);
	this->tcpConnMap[connfd] = newConn;
	this->entranceLoop.addOverseeChannel(tcpConnMap[connfd]->getChanPtr());
}

void TcpServer::start() {
	entranceLoop.loop();
}

TcpServer::~TcpServer() {
	tcpConnMap.clear();
}

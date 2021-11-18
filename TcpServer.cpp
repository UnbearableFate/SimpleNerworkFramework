#include "TcpServer.h"

TcpServer::TcpServer(int port,TcpConnection::MessageHandleFunc func):entranceLoop(), acceptor(Acceptor(port)) {
	this->entranceLoop.addOverseeChannel(acceptor.getChannelPtr());
	this->acceptor.setCreateNewConnCallback(std::bind(&TcpServer::createNewConn, this, std::placeholders::_1,
		std::placeholders::_2, func));
}

void TcpServer::createNewConn(int connfd, sockaddr_in cliAddr,TcpConnection::MessageHandleFunc func) {
	auto newConn =  std::make_shared<TcpConnection>(connfd, cliAddr);
	newConn->setMessageHandleCallback(func);
	this->tcpConnMap[connfd] = newConn;
	this->entranceLoop.addOverseeChannel(tcpConnMap[connfd]->getChanPtr());
}

void TcpServer::start() {
	entranceLoop.loop();
}

TcpServer::~TcpServer() {
	tcpConnMap.clear();
}

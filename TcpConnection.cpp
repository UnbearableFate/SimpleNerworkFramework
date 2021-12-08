#include "TcpConnection.h"
#include "EventLoop.h"
#include <arpa/inet.h>
#include <iostream>

TcpConnection::TcpConnection(int f, sockaddr_in cAddr):tcpConnChan(f),cliAddr(cAddr) {
	tcpConnChan.enableEvent(Channel::READ_EVE);
	tcpConnChan.setReadCallback(std::bind(&TcpConnection::readFromConn,this));
	tcpConnChan.setWriteCallback(std::bind(&TcpConnection::writeToConn, this));
}

void TcpConnection::writeToConn() {
	bool ok = sendBuffer.send(tcpConnChan.getFd());
	if (ok) {
		tcpConnChan.disableEvent(Channel::WRITE_EVE);
		tcpConnChan.update();
	}
}

void TcpConnection::readFromConn() {
	bool ok = receiveBuffer.receive(tcpConnChan.getFd());
	if (ok) {
		messageHandleCallback(receiveBuffer);
	}
	else
	{
		tcpConnChan.getOwnerLoop()->addPendingFunc(this->closeCallback);
	}
}

void TcpConnection::CloseConn() {
	tcpConnChan.getOwnerLoop()->removeChannel(&tcpConnChan);
}

void TcpConnection::send(std::vector<char>& data) {
	sendBuffer.receive(data);
	tcpConnChan.enableEvent(Channel::WRITE_EVE);
	tcpConnChan.update();
}

TcpConnection::~TcpConnection() {
	std::cout << "byebye" << std::endl;
}

std::string TcpConnection::getCliAddrStr() { 
	char addrStr[INET_ADDRSTRLEN]; 
	auto ptr = inet_ntop(AF_INET, &this->cliAddr.sin_addr, addrStr, sizeof(addrStr));
	return std::string(addrStr);
}

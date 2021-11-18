#include "TcpConnection.h"

TcpConnection::TcpConnection(int f, sockaddr_in cAddr):tcpConnChan(f, EPOLLIN),cliAddr(cAddr) {
	printf("new connection");
	tcpConnChan.setReadCallback(std::bind(&TcpConnection::readFromConn,this));
}

void TcpConnection::writeToConn() {
	int n;
	if (!sendBuffer.empty()) {
		n = write(tcpConnChan.getFd(), &*sendBuffer.begin(), sendBuffer.size());
	}
	if (n == sendBuffer.size()) {
		sendBuffer.clear();
	}
}

void TcpConnection::readFromConn() {
	receiveBuffer.resize(1024);
	int n = read(tcpConnChan.getFd(), &*receiveBuffer.begin(), 1024);
	//messageHandleCallback(&*receiveBuffer.begin());
	sendBuffer.swap(receiveBuffer);
	writeToConn();
}

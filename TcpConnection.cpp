#include "TcpConnection.h"

TcpConnection::TcpConnection(int f, sockaddr_in cAddr):tcpConnChan(f),cliAddr(cAddr),receiveBuffer(4096) {
	tcpConnChan.enableEvent(Channel::READ_EVE);
	tcpConnChan.setReadCallback(std::bind(&TcpConnection::readFromConn,this));
	tcpConnChan.setWriteCallback(std::bind(&TcpConnection::writeToConn, this));
}

void TcpConnection::writeToConn() {
	int n;
	if (!sendBuffer.empty()) {
		n = write(tcpConnChan.getFd(), &*sendBuffer.begin(), sendBuffer.size());
	}
	if (n == sendBuffer.size()) {
		sendBuffer.clear();
		tcpConnChan.disableEvent(Channel::WRITE_EVE);
		tcpConnChan.update();
	}
}

void TcpConnection::readFromConn() {
	int n = read(tcpConnChan.getFd(), &*receiveBuffer.begin(), 4096);
	messageHandleCallback(receiveBuffer);
}

void TcpConnection::send(std::vector<char>& data) {
	sendBuffer.insert(sendBuffer.end(), data.begin(), data.end());
	tcpConnChan.enableEvent(Channel::WRITE_EVE);
	tcpConnChan.update();
}

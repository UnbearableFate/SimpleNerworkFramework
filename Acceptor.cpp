#include "Acceptor.h"
Acceptor::Acceptor(int port):sockfd(socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP)), acceptChan(sockfd, EPOLLIN) {
	servAddr = sockaddr_in();
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = INADDR_ANY;
	servAddr.sin_port = htons(port);
	bind(sockfd, (sockaddr*)&servAddr, sizeof(servAddr));
	listen(sockfd, 1024);
	this->acceptChan.setReadCallback(std::bind(&Acceptor::acceptWhenReady, this));
}

void Acceptor::acceptWhenReady() {
	sockaddr_in cliAddr;
	socklen_t len = sizeof(cliAddr);
	int connfd = accept(this->sockfd, (sockaddr*)&cliAddr, &len);
	if (connfd > 0) {
		createNewConnCallback(connfd, cliAddr);
	}
}

#include"TcpServer.h"
#include"EventLoop.h"


void hh() {
	printf("haha");
}
int main()
{
	auto f = std::function<void(void)>(hh);
	TcpServer serv(23234, f);
	serv.start();
	return 0;
}

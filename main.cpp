#include"TcpServer.h"
#include"EventLoop.h"
#include"TcpConnection.h"
#include<memory>
#include<vector>
#include<iostream>
using namespace std;
void hh(const std::shared_ptr<TcpConnection>& conn, std::vector<char>& data) {
	for (auto c : data) {
		if (c == '\0') {
			break;
		}
		cout << c << endl;
	}
	conn->send(data);
}
int main()
{
	TcpServer serv(23234, hh);
	serv.start();
	return 0;
}

#include"TcpServer.h"
#include"EventLoop.h"
#include"TcpConnection.h"
#include<memory>
#include<vector>
#include<iostream>
#include"Buffer.h"
using namespace std;
void hh(TcpConnection* conn, Buffer data) {
	vector<char> res;
	for (auto c : data) {
		if (c == '\0') {
			break;
		}
		cout << c;
		res.push_back(c);
		res.push_back('J');
	}
	cout << endl;
	conn->send(res);
}
int main()
{
	TcpServer serv(23234, hh);
	serv.start();
	return 0;
}

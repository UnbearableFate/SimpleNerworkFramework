#pragma once
#include<vector>
class WriteBuffer
{
private:
	std::vector<char> data;
	size_t begIndex;
	size_t endIndex;
public:
	WriteBuffer() :data(1024),begIndex(0),endIndex(0){}
	void receive(std::vector<char>& str);
	bool send(int fd);
};


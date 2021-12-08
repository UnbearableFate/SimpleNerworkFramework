#pragma once
#include <vector>
#include <sys/uio.h>
class Buffer
{
private:
	std::vector<char> data;
	size_t usedSize;
public:
	Buffer() :data(1024), usedSize(0) {}
	bool receive(int fd);
	std::vector<char>::iterator begin() { return data.begin(); }
	std::vector<char>::iterator end() { return data.begin() + usedSize; }
	std::vector<char>::const_iterator begin() const { return data.begin(); }
	std::vector<char>::const_iterator end() const { return data.begin() + usedSize; }
	char operator[](size_t i) const { return data[i]; }
};

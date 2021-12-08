#include "WriteBuffer.h"
#include <unistd.h>
void WriteBuffer::receive(std::vector<char>& str) {
	if (data.size() - endIndex < str.size()) {
		data.resize(endIndex + str.size());
	}
	std::copy(str.begin(), str.end(), data.begin() + endIndex);
	endIndex += str.size();
}

bool WriteBuffer::send(int fd) {
	int n = write(fd, &*(data.begin() + begIndex), endIndex - begIndex);
	if (n == endIndex - begIndex) {
		endIndex = begIndex = 0;
		return true;
	}
	begIndex += n;
	return false;
}

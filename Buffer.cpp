#include "Buffer.h"

bool Buffer::receive(int fd) {
	iovec temp[2];
	temp[0].iov_base = &*data.begin();
	temp[0].iov_len = data.size();
	char extrabuf[65536];
	temp[1].iov_base = extrabuf;
	temp[1].iov_len = sizeof extrabuf;
	int iovcnt = data.size() < 65536 ? 2 : 1;
	int n = readv(fd, temp, iovcnt);
	if (n == 0) {
		return false;
	}
	if (n > data.size()) {
		data.insert(data.end(), extrabuf,extrabuf+ (n - data.size()));
	}
	usedSize = n;
	return true;
}
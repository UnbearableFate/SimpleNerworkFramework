#include "Channel.h"
#include <unistd.h>
void Channel::handleIO() {
    if (rEvent & (EPOLLERR ))
    {
        if (errorCallback) errorCallback();
    }
    if (rEvent & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        if (readCallback) readCallback();
    }
    if (rEvent & EPOLLOUT)
    {
        if (writeCallback) writeCallback();
    }
}

Channel::~Channel() {
    this->ownerLoop = nullptr;
    close(this->fd);
}

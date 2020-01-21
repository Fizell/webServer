//
// Created by parallels on 2020/1/19.
//

#include "Task.h"


Task::Task(EventLoop *loop, int fd) : loop_(loop), epoll_(new Epoll), fd_(fd) {}

Task::~Task() {}

void Task::eventHandle() {
    if (rfd_ == fd_) {
        connHandle_();
    } else if (revents & EPOLLIN) {
        readHandle_();
    } else if (revents & EPOLLOUT) {
        writeHandle_();
    } else {

    }
    revents = 0;
    fflush(stdout);
}
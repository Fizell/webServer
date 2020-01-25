//
// Created by parallels on 2020/1/19.
//

#include "Task.h"


Task::Task(EventLoop *loop, int fd) : loop_(loop), epoll_(loop->epoll_), fd_(fd), isMainLoop_(false) {}
Task::Task(int fd) : epoll_(new Epoll), fd_(fd), isMainLoop_(false) {

}
Task::~Task() {
    printf("task free\n");
    fflush(stdout);
    //holder_.reset();
    //delete epoll_;
}



void Task::eventHandle() {
    if(isMainLoop())
        connHandle_();
    else if (revents & (EPOLLIN)) {
        readHandle_();
    }
    else if (revents & (EPOLLOUT)) {
        writeHandle_();
    }
    else {
    }
    revents = 0;
    rfd_ = 0;
    fflush(stdout);
}

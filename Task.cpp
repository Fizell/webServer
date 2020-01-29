//
// Created by parallels on 2020/1/19.
//

#include "Task.h"
#include "HttpData.h"


Task::Task(EventLoop *loop, int fd) : loop_(loop), epoll_(loop->epoll_), fd_(fd), isMainLoop_(false), events(0), revents(0) {}

Task::~Task() {
    if(DEBUG) {
        printf("task free\n");
        fflush(stdout);
    }
    //holder_.reset();
    //delete epoll_;
}



void Task::eventHandle() {
    if(isMainLoop()) {
        connHandle_();
        //usleep(100);
    }

    else if (revents & (EPOLLIN)) {
        readHandle_();
    }
    else if (revents & (EPOLLOUT)) {
        //writeHandle_();
    }
    revents = 0;
    rfd_ = 0;
    fflush(stdout);
    if(getHolder())
        if(getHolder()->isClose())
            epoll_->removeEpoll(this);
}

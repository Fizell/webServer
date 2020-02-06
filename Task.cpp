//
// Created by parallels on 2020/1/19.
//

#include "Task.h"
#include "HttpData.h"

//每个HttpData代表一个连接，持有一个Task,Task有事件和需要调用的回调函数等必要信息
Task::Task(EventLoop *loop, int fd) : loop_(loop), epoll_(loop->epoll_), fd_(fd), isMainLoop_(false), events(0), revents(0) {}

Task::~Task() {
    if(DEBUG) {
        printf("task free\n");
        fflush(stdout);
    }
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
    //关闭连接
    /*
    if(getHolder())
        if(getHolder()->isClose()) {
            getHolder()->quit();
            epoll_->removeEpoll(this);
        }
        */

}

void Task::clearHolder() {
    holder_ = NULL;
}
//
// Created by parallels on 2020/1/20.
//

#include "EventLoop.h"
#include "UtilFun.h"
#include <sys/eventfd.h>
#include "UtilFun.h"

ssize_t writen(int fd, char *buff, size_t n);

int createEventfd() {
    int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0) {
        ERR_MSG("create eventfd error");
        exit(0);
    }
    return evtfd;
}

//向event_fd_发送一个信号使线程从epoll_wait状态激活，同时在server中更新了新的epoll，以执行新的事件
void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = writen2(event_fd_, (char*)(&one), sizeof one);
    if (n != sizeof one) {
        printf("wakeup a thread error\n");
    }
    else
        if(DEBUG)
            printf("wakeup a thread\n");
    fflush(stdout);
}

EventLoop::EventLoop() :
    event_fd_(createEventfd()), wait_Task_(new Task(this, event_fd_)), epoll_(new Epoll), looping_(false), quit_(false)  {
    wait_Task_->setReadHandle(std::bind(&EventLoop::readHandle, this));
    //epoll_->addEpoll(wait_Task_);
}

EventLoop::~EventLoop() {
    printf("delete loop\n");
    fflush(stdout);
}

void EventLoop::readHandle() {
    uint64_t one = 1;
    ssize_t n = readn(event_fd_, &one, sizeof one);
    if (n != sizeof one) {
        printf("wakeup error\n");
        //looping_ = true;
    }
    else {
        if(DEBUG)
            printf("wakeup success\n");
        looping_ = true;
    }
    fflush(stdout);


    //wait_Task_->epoll_->addEpoll(EPOLLIN);
}
//事件循环
void EventLoop::loop() {
    //epoll_->addEpoll(wait_Task_);
    while(!quit_) {
        fflush(stdout);
        std::vector<std::shared_ptr<Task> > req = epoll_->poll();
        for(auto &it : req) it->eventHandle();
        epoll_->handleTimer();
    }


}
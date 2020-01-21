//
// Created by parallels on 2020/1/20.
//

#include "EventLoop.h"
#include "UtilFun.h"
#include <sys/eventfd.h>
#include "UtilFun.h"

int createEventfd() {
    int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0) {
        ERR_MSG("create eventfd error");
        exit(0);
    }
    return evtfd;
}

void EventLoop::wakeup() {
    uint64_t one = 1;
    ssize_t n = writen(event_fd_, (char*)(&one), sizeof one);
    if (n != sizeof one) {
        printf("wakeup a thread\n");
    }
}

EventLoop::EventLoop() :
    event_fd_(createEventfd()), wait_Task_(new Task(this, event_fd_)), epoll_(new Epoll), looping_(false), quit_(false)  {
    wait_Task_->setReadHandle(std::bind(&EventLoop::readHandle, this));
    epoll_->addEpoll(wait_Task_);
}

EventLoop::~EventLoop() {}

void EventLoop::readHandle() {
    uint64_t one = 1;
    ssize_t n = readn(event_fd_, &one, sizeof one);
    if (n != sizeof one) {
        printf("wakeup success\n");
        looping_ = true;
    }
    //wait_Task_->epoll_->addEpoll(EPOLLIN);
}

void EventLoop::loop() {
    //epoll_->addEpoll(wait_Task_);
    while(!quit_) {
        fflush(stdout);
        std::vector<Task *> req = epoll_->poll();
        for(auto &it : req) it->eventHandle();
    }


}
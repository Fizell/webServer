//
// Created by parallels on 2020/1/20.
//

#include <unistd.h>
#include "EventLoopThread.h"

EventLoopThread::EventLoopThread() :
    loop_(NULL),
    thread_(std::bind(&EventLoopThread::run, this), "EventLoopThread"),
    mutex_(),
    cond_(mutex_)
{}


EventLoopThread::~EventLoopThread() {}

void EventLoopThread::run() {
    {
        MutexLockGuard lock(mutex_);
        usleep(100000);
        cond_.notify();
    }
    while(loop_ == NULL);
    loop_->loop();
}

EventLoop *EventLoopThread::startLoop() {
    EventLoop *loop = new EventLoop();
    thread_.start();
    loop_ = loop;
    loop_->wait_Task_->epoll_->addEpoll(loop_->wait_Task_);
    {
        MutexLockGuard lock(mutex_);
        cond_.wait();
    }

    return loop_;
}
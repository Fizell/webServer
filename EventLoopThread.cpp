//
// Created by parallels on 2020/1/20.
//

#include <unistd.h>
#include "EventLoopThread.h"

EventLoopThread::EventLoopThread() :
    thread_(std::bind(&EventLoopThread::run, this), "EventLoopThread"), loop_(NULL)
{}


EventLoopThread::~EventLoopThread() {}

void EventLoopThread::run() {
    loop_->loop();
}

EventLoop *EventLoopThread::startLoop() {
    EventLoop loop;
    thread_.start();
    loop_ = &loop;
    loop_->wait_Task_->epoll_->addEpoll(loop_->wait_Task_);
    sleep(2);
    return loop_;
}
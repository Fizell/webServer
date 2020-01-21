//
// Created by parallels on 2020/1/20.
//

#include <unistd.h>
#include "EventLoopThread.h"

EventLoopThread::EventLoopThread() :
    loop_(NULL),
    thread_(std::bind(&EventLoopThread::run, this), "EventLoopThread")
{}


EventLoopThread::~EventLoopThread() {}

void EventLoopThread::run() {
    while(loop_ == NULL);
    loop_->loop();
}

EventLoop *EventLoopThread::startLoop() {
    EventLoop *loop = new EventLoop();
    thread_.start();
    loop_ = loop;
    loop_->wait_Task_->epoll_->addEpoll(loop_->wait_Task_);
    sleep(1);
    return loop_;
}
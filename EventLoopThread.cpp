//
// Created by parallels on 2020/1/20.
//

#include "EventLoopThread.h"

EventLoopThread::EventLoopThread() :
    thread_(std::bind(&EventLoopThread::run, this), "EventLoopThread"), loop_(NULL)
{}


EventLoopThread::~EventLoopThread() {}

void EventLoopThread::run() {

}

EventLoop *EventLoopThread::startLoop() {
    EventLoop loop;
    loop_ = &loop;

    loop_->loop();
    return loop_;
}
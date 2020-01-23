//
// Created by parallels on 2020/1/20.
//

#include <unistd.h>
#include "EventLoopThread.h"

EventLoopThread::EventLoopThread() :
    loop_(NULL),
    thread_(std::bind(&EventLoopThread::run, this), "EventLoopThread"),
    mutex_(),
    cond_(mutex_),
    flag_(false)
{}


EventLoopThread::~EventLoopThread() {}

void EventLoopThread::run() {

    //usleep(1000000);
    mutex_.lock();
    while(!flag_);
    usleep(100);
    cond_.notify();
    mutex_.unlock();
    while(loop_ == NULL);
    loop_->loop();
}

EventLoop *EventLoopThread::startLoop() {
    EventLoop *loop = new EventLoop();
    loop_ = loop;
    loop_->wait_Task_->epoll_->addEpoll(loop_->wait_Task_);
    mutex_.lock();
    flag_ = false;
    thread_.start();
    flag_ = true;
    cond_.wait();

    usleep(100000);//需要等到进入到loop的循环，startLoop才能返回
    mutex_.unlock();
    return loop_;
}
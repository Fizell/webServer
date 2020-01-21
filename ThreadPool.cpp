//
// Created by parallels on 2020/1/20.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(EventLoop *baseloop) : baseLoop_(baseloop), next_(0) {}

ThreadPool::~ThreadPool() {}

void ThreadPool::creatThreadPool() {
    for(int i = 0; i < MAX_THREAD; i++) {
        std::shared_ptr<EventLoopThread> t(new EventLoopThread());
        loops_.push_back(t->startLoop());
    }
    printf("ThreadPool create success\n");
}

EventLoop *ThreadPool::getNext() {
    EventLoop *loop = baseLoop_;
    if (!loops_.empty()) {
        loop = loops_[next_];
        next_ = (next_ + 1) % MAX_THREAD;
    }
    return loop;
}
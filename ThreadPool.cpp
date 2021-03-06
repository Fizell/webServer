//
// Created by parallels on 2020/1/20.
//

#include <unistd.h>
#include "ThreadPool.h"

ThreadPool::ThreadPool(EventLoop *baseloop) : baseLoop_(baseloop), next_(0), mutex_(), cond_(mutex_) {}

ThreadPool::~ThreadPool() {}

void ThreadPool::creatThreadPool() {
    for(int i = 0; i < MAX_THREAD; i++) {
        std::shared_ptr<EventLoopThread> t(new EventLoopThread());
        {
            mutex_.lock();
            loops_.push_back(t->startLoop());
            mutex_.unlock();
        }

    }
    printf("ThreadPool create success\n");
}
//获取下一个线程事件循环指针，每一个连接都使用下一个线程，线程负载均衡
EventLoop *ThreadPool::getNext() {
    EventLoop *loop = baseLoop_;
    if (!loops_.empty()) {
        loop = loops_[next_];
        next_ = (next_ + 1) % MAX_THREAD;
    }
    return loop;
}
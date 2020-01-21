//
// Created by parallels on 2020/1/20.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(EventLoop baseloop) : baseLoop_(baseloop) {}

ThreadPool::~ThreadPool() {}

void ThreadPool::creatThreadPool() {
    for(int i = 0; i < MAX_THREAD; i++) {
        std::shared_ptr<EventLoopThread> t(new EventLoopThread());
        loops_.push_back(t->startLoop());
    }
    printf("ThreadPool create success\n");
}

int ThreadPool::getNext() {

}
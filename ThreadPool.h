//
// Created by parallels on 2020/1/20.
//

#ifndef WEB_SERVER1_1_THREADPOOL_H
#define WEB_SERVER1_1_THREADPOOL_H

#include <vector>
#include "EventLoopThread.h"
#include "WebLimit.h"
class ThreadPool {
public:
    ThreadPool(EventLoop *baseLoop);
    ~ThreadPool();
    EventLoop * getNext();
    void creatThreadPool();

    EventLoop *baseLoop_;
    //std::vector<EventLoopThread *> loop_threads_;
    std::vector<EventLoop *> loops_;
    int next_;
    Condition cond_;
    MutexLock mutex_;
private:

};


#endif //WEB_SERVER1_1_THREADPOOL_H

//
// Created by parallels on 2020/1/20.
//

#ifndef WEB_SERVER1_1_EVENTLOOPTHREAD_H
#define WEB_SERVER1_1_EVENTLOOPTHREAD_H


#include "Thread.h"
#include "Epoll.h"
#include "EventLoop.h"
#include "Condition.h"

class EventLoopThread {
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop *startLoop();
    void run();

private:
    EventLoop *loop_;
    Thread thread_;
    Condition cond_;
    MutexLock mutex_;
    bool flag_;
};


#endif //WEB_SERVER1_1_EVENTLOOPTHREAD_H

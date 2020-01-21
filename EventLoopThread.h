//
// Created by parallels on 2020/1/20.
//

#ifndef WEB_SERVER1_1_EVENTLOOPTHREAD_H
#define WEB_SERVER1_1_EVENTLOOPTHREAD_H


#include "Thread.h"
#include "Epoll.h"
#include "EventLoop.h"

class EventLoopThread {
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop *startLoop();
    void run();

private:
    Thread thread_;
    EventLoop *loop_;

};


#endif //WEB_SERVER1_1_EVENTLOOPTHREAD_H

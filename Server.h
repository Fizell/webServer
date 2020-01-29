//
// Created by parallels on 2020/1/19.
//

#ifndef WEB_SERVER1_1_SERVER_H
#define WEB_SERVER1_1_SERVER_H

#include "Task.h"
#include "EventLoop.h"
#include "ThreadPool.h"
#include "MutexLock.h"

class Task;
class Server {
public:
    Server(EventLoop* loop, int port);
    ~Server();
    int startListen(int port);
    void start();
    void newConnHandle();
    void test1();
    void test2();
    void test3();
private:
    int listen_fd;
    EventLoop *loop_;
    Task *task_;
    ThreadPool *threadPool_;
    char ipbuf_tmp_[50];
    int n;
    char buff[MAXLINE];
    MutexLock mutex_;
};



#endif //WEB_SERVER1_1_SERVER_H

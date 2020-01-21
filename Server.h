//
// Created by parallels on 2020/1/19.
//

#ifndef WEB_SERVER1_1_SERVER_H
#define WEB_SERVER1_1_SERVER_H

#include "Task.h"
#include "EventLoop.h"

class Task;
class Server {
public:
    Server(EventLoop* loop, int port);
    ~Server();
    int startListen(int port);
    void start();
    void newConnHandle();
    void readHandle();
    void writeHandle();
private:
    EventLoop *loop_;
    std::shared_ptr<Task> task_;
    char ipbuf_tmp_[50];
    int n;
    char buff[MAXLINE];
};



#endif //WEB_SERVER1_1_SERVER_H

//
// Created by parallels on 2020/1/19.
//

#ifndef WEB_SERVER1_1_SERVER_H
#define WEB_SERVER1_1_SERVER_H

#include "Task.h"

class Task;
class Server {
public:
    Server(int port);
    ~Server();
    int startListen(int port);
    void start();
    void newConnHandle();
    void readHandle();
    void writeHandle();
private:
    std::shared_ptr<Task> task_;
    char ipbuf_tmp_[50];
    int n;
    char buff[MAXLINE];
};



#endif //WEB_SERVER1_1_SERVER_H

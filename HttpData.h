//
// Created by parallels on 2020/1/21.
//

#ifndef WEB_SERVER1_1_HTTPDATA_H
#define WEB_SERVER1_1_HTTPDATA_H
#include "UtilFun.h"
#include "WebLimit.h"
#include "Task.h"
#include <unp.h>
#include <functional>

class HttpData {
public:
    HttpData(EventLoop *loop, int fd);
    ~HttpData();
    void readHandle();
    void writeHandle();

    Task *getTask() {return task_;}
private:
    int fd_;
    char ipbuf_tmp_[50];
    int n;
    char buff[MAXLINE];
    Task *task_;
    EventLoop *loop_;
};


#endif //WEB_SERVER1_1_HTTPDATA_H

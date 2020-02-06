//
// Created by parallels on 2020/1/19.
//

#ifndef WEB_SERVER1_1_EPOLL_H
#define WEB_SERVER1_1_EPOLL_H

#include "Task.h"
#include <memory>
#include <vector>
#include <sys/epoll.h>
#include "WebLimit.h"
#include "MutexLock.h"
#include "Timer.h"

class Task;
class HttpData;
class Timer;
class TimerManager;
class Epoll {
public:
    Epoll();
    ~Epoll();
    std::vector<Task *> poll();
    void addEpoll(Task *task);
    void removeEpoll(Task *task);
    void handleTimer();
    void addTimer(Task *task);
    int fd_;
    int epollfd_;
    struct epoll_event events[MAX_EVENT];
    //主要为了epoll的循环可以取得事件对应的task，以执行task中回调函数
    Task *fd_to_task_[MAXFDS];
    //主要为了epoll的循环可以取得事件对应的http，目前主要是关闭连接使用
    std::shared_ptr<HttpData>fd_to_http_[MAXFDS];

private:
    TimerManager *timer_manager_;
    MutexLock mutex_;
};


#endif //WEB_SERVER1_1_EPOLL_H

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


class Task;
class HttpData;
class Epoll {
public:
    Epoll();
    ~Epoll();
    std::vector<Task *> poll();
    void addEpoll(Task *task);
    void removeEpoll(Task *task);
    void updataEpoll(Task *task);

    int fd_;
    int epollfd_;
    struct epoll_event events[MAX_EVENT];
    Task *fd_to_task_[MAXFDS];
    std::shared_ptr<HttpData>fd_to_http_[MAXFDS];

private:
    MutexLock mutex_;
};


#endif //WEB_SERVER1_1_EPOLL_H

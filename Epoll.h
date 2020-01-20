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

class Task;
class Epoll {
public:
    Epoll();
    ~Epoll();
    std::vector<std::shared_ptr<Task>> poll();
    void addEpoll(std::shared_ptr<Task> task);
    void removeEpoll(std::shared_ptr<Task> task);
    void updataEpoll(std::shared_ptr<Task> task);

    int fd_;
    int epollfd_;
    struct epoll_event events[MAX_EVENTS];
    std::shared_ptr<Task> fd_to_task_[MAX_EVENTS];

private:
};


#endif //WEB_SERVER1_1_EPOLL_H

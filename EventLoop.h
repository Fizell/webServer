//
// Created by parallels on 2020/1/20.
//

#ifndef WEB_SERVER1_1_EVENTLOOP_H
#define WEB_SERVER1_1_EVENTLOOP_H

#include <memory>
#include <vector>
#include "Task.h"
#include "Epoll.h"

class Epoll;
class Task;
class EventLoop {
public:
    EventLoop();
    ~EventLoop();
    void readHandle();
    void writeHandle();
    void loop();
    void wakeup();
private:
    std::shared_ptr<Task> wait_Task_;
    int event_fd_;
    Epoll *epoll_;
};


#endif //WEB_SERVER1_1_EVENTLOOP_H

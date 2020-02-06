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
    void loop();
    void wakeup();

    int event_fd_;
    std::shared_ptr<Task> wait_Task_;
    Epoll *epoll_;
    bool looping_;
    bool quit_;
private:


};


#endif //WEB_SERVER1_1_EVENTLOOP_H

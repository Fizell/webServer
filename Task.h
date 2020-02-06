//
// Created by parallels on 2020/1/19.
//

#ifndef WEB_SERVER1_1_TASK_H
#define WEB_SERVER1_1_TASK_H


#include <stdint.h>
#include "Epoll.h"
#include <functional>
#include "EventLoop.h"

class EventLoop;
class Epoll;
class HttpData;
class Task {
public:
    Task(EventLoop *loop, int fd);
    ~Task();
    typedef std::function<void()> func;

    int fd_;
    int rfd_;
    __uint32_t events;
    __uint32_t revents;

    func connHandle_;
    func readHandle_;
    func writeHandle_;

    int getFd() {return fd_;}
    //void addToEpoll() {epoll_->addEpoll(this);}
    Epoll *epoll_;
    void setConnHandle(func &&func_) {connHandle_ = func_;}
    void setReadHandle(func &&func_) {readHandle_ = func_;}
    void setWriteHandle(func &&func_) {writeHandle_ = func_;}
    void eventHandle();
    bool isMainLoop() {return isMainLoop_;}
    void setMainLoop() {isMainLoop_ = true;}

    void setHolder(std::shared_ptr<HttpData> holder) { holder_ = holder; }
    std::shared_ptr<HttpData> getHolder() { return holder_; }
    void clearHolder();

private:
    std::shared_ptr<HttpData> holder_;
    EventLoop *loop_;
    bool isMainLoop_;

};


#endif //WEB_SERVER1_1_TASK_H

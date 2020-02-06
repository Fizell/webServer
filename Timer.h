//
// Created by parallels on 2020/2/1.
//

#ifndef WEB_SERVER1_1_TIMER_H
#define WEB_SERVER1_1_TIMER_H


#include <memory>
#include "HttpData.h"
#include <deque>
#include <queue>
#include "Epoll.h"

using namespace std;
class HttpData;
class Epoll;
class Timer {
public:
    Timer(std::shared_ptr<HttpData> http, Epoll *epoll_);
    ~Timer();
    void updateTime();
    bool checkTime();
    void setQuit();
    void clearTime();
    bool isQuit() {return quit_;}
    size_t getTime() const { return time_; }
    std::shared_ptr<HttpData> http_;
private:
    bool quit_;
    size_t time_;

    Epoll *epoll_;
};

struct TimerCmp {
    bool operator()(std::shared_ptr<Timer> &a,
                    std::shared_ptr<Timer> &b) const {
        return a->getTime() > b->getTime();
    }
};

class TimerManager {
public:
    TimerManager(Epoll *epoll);
    ~TimerManager();
    void addTimer(std::shared_ptr<Timer> timer);
    void handleCheckTimer();

private:
    std::priority_queue<std::shared_ptr<Timer>, std::deque<std::shared_ptr<Timer>>, TimerCmp> timerNodeQueue_;
    Epoll *epoll_;
    MutexLock mutex_;
};
#endif //WEB_SERVER1_1_TIMER_H

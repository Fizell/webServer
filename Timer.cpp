//
// Created by parallels on 2020/2/1.
//
#include "Timer.h"
#include <time.h>
#include <sys/time.h>
#include "WebLimit.h"

Timer::Timer(std::shared_ptr<HttpData> http, Epoll *epoll) : http_(http), quit_(false), time_(0), epoll_(epoll) {
    struct timeval now;
    gettimeofday(&now, NULL);
    time_ = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + DEFAULT_KEEP_ALIVE_TIME;

}

Timer::~Timer() {
    if(DEBUG) {
        printf("Timer free\n");
        fflush(stdout);
    }
}

void Timer::setQuit() {
    quit_ = true;
    http_.reset();
}
void Timer::updateTime() {
    struct timeval now;
    gettimeofday(&now, NULL);
    time_ = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + DEFAULT_KEEP_ALIVE_TIME;
}

bool Timer::checkTime() {
    struct timeval now;
    gettimeofday(&now, NULL);
    size_t temp = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));
    if (temp < time_)
        return true;
    else {
        if(quit_ != true)
            epoll_->removeEpoll(http_->getTask());
        http_.reset();
        quit_ = true;
        return false;
    }

}


TimerManager::TimerManager(Epoll *epoll) : epoll_(epoll){}
TimerManager::~TimerManager() {}

void TimerManager::addTimer(std::shared_ptr<HttpData> http) {
    std::shared_ptr<Timer> new_node(new Timer(http, epoll_));
    http->linkTimer(new_node);
    timerNodeQueue_.push(new_node);
}

void TimerManager::handleCheckTimer() {
    // MutexLockGuard locker(lock);
    while (!timerNodeQueue_.empty()) {
        std::shared_ptr<Timer> ptimer_now = timerNodeQueue_.top();
        if (ptimer_now->isQuit())
            timerNodeQueue_.pop();
        else if (ptimer_now->checkTime() == false)
            timerNodeQueue_.pop();
        else
            break;
    }
}
//
// Created by parallels on 2020/1/19.
//

#include "Epoll.h"
#include <sys/epoll.h>
#include <unp.h>
#include "WebLimit.h"
#include "UtilFun.h"

Epoll::Epoll() : epollfd_(epoll_create(MAXFDS)), mutex_(), timer_manager_(new TimerManager(this)) {}
Epoll::~Epoll() {
    printf("http free\n");
    fflush(stdout);
}
//新连接增加epoll关注事件
void Epoll::addEpoll(Task *task) {
    fd_ = task->getFd();
    struct epoll_event ev;
    ev.data.fd = fd_;
    ev.events = EPOLLIN | EPOLLONESHOT;
    fd_to_task_[fd_] = task;
    fd_to_http_[fd_] = task->getHolder();
    epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd_, &ev);
}
//等待事件,获取任务
std::vector<Task *> Epoll::poll() {
    int events_count;
    for (;;) {
        events_count=epoll_wait(epollfd_,events, MAX_EVENT, EPOLL_TIMEWAIT);
        if(events_count < 0) {
            continue;
        }
        else if(events_count == 0) {
            //continue;
        }

        std::vector<Task *> req;
        for(int i = 0; i< events_count; i++) {
            if(fd_to_task_[events[i].data.fd] == NULL)
                continue;
            Task *cur_req = fd_to_task_[events[i].data.fd];
            //cur_req->rfd_ = events[i].data.fd;
            cur_req->revents = events[i].events;
            cur_req->events = 0;
            req.push_back(cur_req);
            fflush(stdout);

        }
        return req;
    }
}

//删除的epoll关注事件，释放内存
void Epoll::removeEpoll(Task *task) {
    int fd = task->getFd();
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLONESHOT;
    if (epoll_ctl(task->epoll_->epollfd_, EPOLL_CTL_DEL, fd, &event) < 0) {
        //
    }
    //reset Task的引用
    fd_to_task_[fd]->getHolder().reset();
    delete fd_to_task_[fd];
    fd_to_task_[fd] = NULL;
    //reset Epoll的引用
    fd_to_http_[fd].reset();
    fd_to_http_[fd] = NULL;
}

void Epoll::handleTimer() {timer_manager_->handleCheckTimer();}

void Epoll::addTimer(std::shared_ptr<HttpData> http) {timer_manager_->addTimer(http);}
//
// Created by parallels on 2020/1/19.
//

#include "Epoll.h"
#include <sys/epoll.h>
#include <unp.h>
#include "WebLimit.h"
#include "UtilFun.h"
Epoll::Epoll() : epollfd_(epoll_create(MAX_EVENTS)) {}
Epoll::~Epoll() {}

void Epoll::addEpoll(std::shared_ptr<Task> task) {
    fd_ = task->getFd();
    struct epoll_event ev;
    ev.data.fd = fd_;
    ev.events = EPOLLIN;
    fd_to_task_[fd_] = task;
    epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd_, &ev);
}

std::vector<std::shared_ptr<Task>> Epoll::poll() {
    int events_count, connfd, sockfd, n;
    struct epoll_event ev;
    struct sockaddr_in chiladdr;
    char ipbuf_tmp[50];
    char buff[MAXLINE];
    for (;;) {
        events_count=epoll_wait(epollfd_,events, MAX_EVENTS, EPOLL_TIMEWAIT);
        if(events_count < 0) {
            ERR_MSG("epoll_wait error");
            continue;
        }
        else if(events_count == 0)
            continue;
        std::vector<std::shared_ptr<Task>> req;
        for(int i = 0; i< events_count; i++) {
            std::shared_ptr<Task> cur_req = fd_to_task_[fd_];
            cur_req->rfd_ = events[i].data.fd;
            cur_req->revents = events[i].events;
            cur_req->events = 0;
            req.push_back(cur_req);
            /*
            if (events[i].data.fd == fd_) {
            } else if (events[i].events & EPOLLIN) {

            } else if (events[i].events & EPOLLOUT) {

            }
            fflush(stdout);
             */
        }
        if(req.size() != 0)
            return req;
    }
}

void Epoll::removeEpoll(std::shared_ptr<Task> task) {
    events[task->fd_].events = 0;
    events[task->fd_].data.fd = -1;
}
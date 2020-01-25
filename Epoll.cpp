//
// Created by parallels on 2020/1/19.
//

#include "Epoll.h"
#include <sys/epoll.h>
#include <unp.h>
#include "WebLimit.h"
#include "UtilFun.h"
Epoll::Epoll() : epollfd_(epoll_create(MAXFDS)) {}
Epoll::~Epoll() {
    printf("http free\n");
    fflush(stdout);
}

void Epoll::addEpoll(Task *task) {
    fd_ = task->getFd();
    struct epoll_event ev;
    ev.data.fd = fd_;
    ev.events = EPOLLIN | EPOLLONESHOT;
    fd_to_task_[fd_] = task;
    //fd_to_http_[fd_] = task->getHolder();
    epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd_, &ev);
}

std::vector<Task *> Epoll::poll() {
    int events_count, connfd, sockfd, n;
    struct epoll_event ev;
    struct sockaddr_in chiladdr;
    char ipbuf_tmp[50];
    char buff[MAXLINE];
    for (;;) {
        events_count=epoll_wait(epollfd_,events, MAX_EVENT, EPOLL_TIMEWAIT);
        if(events_count < 0) {
            ERR_MSG("epoll_wait error");
            //exit(0);
            continue;
        }
        else if(events_count == 0)
            continue;
        std::vector<Task *> req;
        for(int i = 0; i< events_count; i++) {
            /*
            if(events[i].data.fd != fd_) {
                events[i].events = 0;
                continue;
            }
             */
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

void Epoll::removeEpoll(Task *task) {
    int fd = task->getFd();
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLONESHOT;
    if (epoll_ctl(task->epoll_->epollfd_, EPOLL_CTL_DEL, fd, &event) < 0) {
        ERR_MSG("epoll_del error");
        exit(0);
    }
    //delete fd_to_task_[fd];
    fd_to_task_[fd] = NULL;
    //delete fd_to_http_[fd];
    //fd_to_http_[fd] = NULL;
}
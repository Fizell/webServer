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
void Epoll::addEpoll(std::shared_ptr<Task> task) {
    mutex_.lock();
    int fd = task->getFd();
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLONESHOT;
    fd_to_task_[fd] = task;
    fd_to_http_[fd] = task->getHolder();
    addTimer(task);
    epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev);
    mutex_.unlock();
}
//等待事件,获取任务
std::vector<std::shared_ptr<Task>> Epoll::poll() {
    int events_count;
    for (;;) {
        events_count=epoll_wait(epollfd_,events, MAX_EVENT, EPOLL_TIMEWAIT);
        if(events_count < 0) {
            continue;
        }
        else if(events_count == 0) {
            //continue;
        }

        std::vector<std::shared_ptr<Task>> req;
        for(int i = 0; i< events_count; i++) {
            if(fd_to_task_[events[i].data.fd] == NULL)
                continue;
            std::shared_ptr<Task> cur_req = fd_to_task_[events[i].data.fd];
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
void Epoll::removeEpoll(std::shared_ptr<Task> task) {
    //在这里加锁会和timer对象互斥造成死锁,由于这里没有使线程不安全的操作，所以不加锁
    mutex_.lock();
    int fd = task->getFd();
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLONESHOT;
    if (epoll_ctl(task->epoll_->epollfd_, EPOLL_CTL_DEL, fd, &event) < 0) {
        //
    }
    //reset Task的引用
    //Task *task_tmp = fd_to_task_[fd];
    fd_to_task_[fd]->getHolder().reset();
    fd_to_task_[fd]->clearHolder();
    fd_to_task_[fd].reset();
    fd_to_task_[fd] = NULL;
    //reset Epoll的引用
    fd_to_http_[fd].reset();
    fd_to_http_[fd] = NULL;
    mutex_.unlock();
}

void Epoll::handleTimer() {
    //mutex_.lock();
    timer_manager_->handleCheckTimer();
    //mutex_.unlock();
}


void Epoll::addTimer(std::shared_ptr<Task> task) {
    shared_ptr<HttpData> t = task->getHolder();
    if (t) {
        std::shared_ptr<Timer> timer = std::make_shared<Timer>(t, this);
        timer_manager_->addTimer(timer);
    }
    else {
        printf("add timer falure\n");
    }
}

//
// Created by parallels on 2020/1/21.
//

#include <sys/epoll.h>
#include "HttpData.h"


HttpData::HttpData(EventLoop *loop, int fd) : fd_(fd), n(0), task_(new Task(loop, fd_)), loop_(loop) {

    //task_->setConnHandle(std::bind(&HttpData::newConnHandle, this));
    task_->setReadHandle(std::bind(&HttpData::readHandle, this));
    task_->setWriteHandle(std::bind(&HttpData::writeHandle, this));
    task_->epoll_ = loop->epoll_;
    //loop->epoll_->removeEpoll(task);
    loop->epoll_->addEpoll(task_);
}

HttpData::~HttpData() {
    printf("http free\n");
    fflush(stdout);
    //delete task_;
}

void HttpData::readHandle() {
    struct sockaddr_in chiladdr;
    int sockfd;

    char ipbuf_tmp[50];
    struct epoll_event ev;
    /*
    ev.data.fd = fd_;
    ev.events = EPOLLIN | EPOLLONESHOT;
    epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, fd_, &ev);

*/
    if ((sockfd = fd_) < 0) {
        ERR_MSG("fd_ error");
        return;
    }

    bzero(&chiladdr, sizeof(chiladdr));
    socklen_t chillen = sizeof(chiladdr);
    getpeername(sockfd, (SA *) &chiladdr, &chillen);

    if ((n = read(sockfd, buff, MAXLINE)) < 0) {
        if (errno == ECONNRESET) {
            bzero(&chiladdr, sizeof(chiladdr));
            socklen_t chillen = sizeof(chiladdr);
            getpeername(sockfd, (SA *) &chiladdr, &chillen);
            loop_->epoll_->removeEpoll(task_);
            //delete loop_;
            close(sockfd);
            printf("close connect [%s : %d]\n",
                   inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),
                   ntohs(chiladdr.sin_port));
            delete this;
            return;
        } else
            ERR_MSG("read error");
    } else if (n == 0) {
        loop_->epoll_->removeEpoll(task_);
        //delete loop_;
        close(sockfd);
        printf("close connect [%s : %d]\n",
               inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),
               ntohs(chiladdr.sin_port));
        delete this;
        return;
    } else {
        buff[n] = '\0';
        printf("receive msg: %s from [%s : %d]\n", buff,
               inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),
               ntohs(chiladdr.sin_port));

        fflush(stdout);
        ev.data.fd = sockfd;
        ev.events = EPOLLOUT | EPOLLONESHOT;
        epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, sockfd, &ev);
    }



}

void HttpData::writeHandle() {
    int sockfd;
    char ipbuf_tmp[50];
    struct epoll_event ev;
    struct sockaddr_in chiladdr;
    sockfd = fd_;
    bzero(&chiladdr, sizeof(chiladdr));
    socklen_t chillen = sizeof(chiladdr);
    getpeername(sockfd, (SA *) &chiladdr, &chillen);
    write(sockfd, buff, n);
    printf("echo msg: %s to [%s : %d]\n", buff,
           inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),
           ntohs(chiladdr.sin_port));

    fflush(stdout);

    ev.data.fd = sockfd;
    ev.events = EPOLLIN | EPOLLONESHOT;
    epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, sockfd, &ev);

}
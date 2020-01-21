//
// Created by parallels on 2020/1/19.
//

#include "Server.h"
#include "UtilFun.h"
#include <unp.h>
#include "WebLimit.h"
#include <functional>

Server::Server(EventLoop* loop, int port) : loop_(loop), task_(new Task(loop_, startListen(port))) {}
Server::~Server() {}

void Server::start() {
    task_->epoll_->addEpoll(task_);

    task_->setConnHandle(std::bind(&Server::newConnHandle, this));
    task_->setReadHandle(std::bind(&Server::readHandle, this));
    task_->setWriteHandle(std::bind(&Server::writeHandle, this));

    for(;;) {
        std::vector<std::shared_ptr<Task>> req;
        req = task_->epoll_->poll();
        for(auto &it : req) it->eventHandle();

    }

}

int Server::startListen(int port) {
    int listenfd, connfd, epfd, nfds, sockfd;
    struct sockaddr_in servaddr, chiladdr;
    char buff[MAXLINE];
    char ipbuf_tmp[50];
    ssize_t n;
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("errno: %2d\t%s\n",errno,strerror(errno));
        ERR_MSG("socket_error");
    }


    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if((bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) != 0) {
        ERR_MSG("bind error");
        printf("errno: %2d\t%s\n",errno,strerror(errno));
        exit(0);
    }

    if((listen(listenfd, LISTENQ)) != 0) {
        ERR_MSG("listen error");
        printf("errno: %2d\t%s\n",errno,strerror(errno));
        exit(0);
    }

    return listenfd;
}

void Server::newConnHandle() {
    int connfd;
    struct sockaddr_in chiladdr;
    struct epoll_event ev;
    bzero(&chiladdr, sizeof(chiladdr));
    socklen_t chillen = sizeof(chiladdr);
    int fd_ = task_->epoll_->fd_;
    connfd = accept(fd_, (SA *) &chiladdr, &chillen);
    if (connfd < 0) {
        ERR_MSG("connfd error(value < 0)");
        return;
    }

    printf("New connect from %s port: %d\n",
           inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp_, sizeof(ipbuf_tmp_)),
           ntohs(chiladdr.sin_port));

    ev.data.fd = connfd;
    ev.events = EPOLLIN;
    //ev.events=EPOLLIN|EPOLLET;
    epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_ADD, connfd, &ev);
}

void Server::readHandle() {
    struct sockaddr_in chiladdr;
    int sockfd;

    char ipbuf_tmp[50];
    struct epoll_event ev;
    if ((sockfd = task_->rfd_) < 0) {
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
            close(sockfd);
            printf("close connect [%s : %d]\n",
                   inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),
                   ntohs(chiladdr.sin_port));
            task_->epoll_->removeEpoll(task_);
        } else
            ERR_MSG("read error");
    } else if (n == 0) {

        close(sockfd);
        printf("close connect [%s : %d]\n",
               inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),
               ntohs(chiladdr.sin_port));
        task_->epoll_->removeEpoll(task_);
    } else {
        buff[n] = '\0';
        printf("receive msg: %s from [%s : %d]\n", buff,
               inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),
               ntohs(chiladdr.sin_port));
    }


    ev.data.fd = sockfd;
    ev.events = EPOLLOUT;
    epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, sockfd, &ev);
}

void Server::writeHandle() {
    int sockfd;
    char ipbuf_tmp[50];
    struct epoll_event ev;
    struct sockaddr_in chiladdr;
    sockfd = task_->rfd_;
    bzero(&chiladdr, sizeof(chiladdr));
    socklen_t chillen = sizeof(chiladdr);
    getpeername(sockfd, (SA *) &chiladdr, &chillen);
    write(sockfd, buff, n);
    printf("echo msg: %s to [%s : %d]\n", buff,
           inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),
           ntohs(chiladdr.sin_port));
    ev.data.fd = sockfd;
    ev.events = EPOLLIN;
    epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, sockfd, &ev);
}
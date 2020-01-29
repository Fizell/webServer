//
// Created by parallels on 2020/1/19.
//

#include "Server.h"
#include "UtilFun.h"
#include <unp.h>
#include "WebLimit.h"
#include <functional>
#include "HttpData.h"

Server::Server(EventLoop* loop, int port) : mutex_(), listen_fd(startListen(port)), threadPool_(new ThreadPool(loop_)), loop_(loop), task_(new Task(loop_, listen_fd)) {}
Server::~Server() {}

void Server::start() {

    threadPool_->creatThreadPool();
    task_->epoll_->addEpoll(task_);
    task_->setMainLoop();
    task_->setConnHandle(std::bind(&Server::newConnHandle, this));

    for(;;) {
        std::vector<Task *> req;
        req = task_->epoll_->poll();
        for(auto &it : req) {
            mutex_.lock();
            it->eventHandle();
            mutex_.unlock();
        }

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

void Server::test1() {
    printf("test1\n");
    fflush(stdout);
}
void Server::test2() {
    printf("test2\n");
    fflush(stdout);
}
void Server::test3() {
    printf("test3\n");
    fflush(stdout);
}
void Server::newConnHandle() {
    //task_->epoll_->addEpoll(task_);
    int fd_ = task_->epoll_->fd_;
    struct epoll_event ev;
    ev.data.fd = fd_;
    ev.events = EPOLLIN | EPOLLONESHOT;
    epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, fd_, &ev);
    int connfd;
    struct sockaddr_in chiladdr;
    bzero(&chiladdr, sizeof(chiladdr));
    socklen_t chillen = sizeof(chiladdr);
    read(fd_, buff, MAXLINE);
    connfd = accept(fd_, (SA *) &chiladdr, &chillen);
    if (connfd < 0) {
        ERR_MSG("connfd error(value < 0)");
        return;
    }

    EventLoop *loop = threadPool_->getNext();
    //原先在http里面创建 task，但是这样子在压测中会造成初始化还没成功就进行到下一语句的情况
    Task *task = new Task(loop, connfd);
    std::shared_ptr<HttpData> http(new HttpData(loop, connfd, task));
    //usleep(30);
    task->setHolder(http);
    if(DEBUG)
        printf("New connect from %s port: %d\n",inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp_, sizeof(ipbuf_tmp_)),ntohs(chiladdr.sin_port));



    /*
    ev.data.fd = connfd;
    ev.events = EPOLLIN;
    //ev.events=EPOLLIN|EPOLLET;
    epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_ADD, connfd, &ev);
     */
}


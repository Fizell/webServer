//
// Created by parallels on 2020/1/20.
//

#include "Thread.h"
Thread::Thread(Thread::func _func, std::string name) : func_(_func), name_(name), start_(0), join_(0) {}

Thread::~Thread() {
    if (start_ && !join_) pthread_detach(tid_);
}

struct Data {
    pthread_t *tid;
    pid_t  *pid;
    std::function<void()> func;
    std::string name;

    Data(pthread_t *tid, pid_t *pid, std::function<void()> func, std::string name) :
    tid(tid), pid(pid), func(func), name(name)
    {}

};

void *startThread(void *obj) {
    Data *data = static_cast<Data*>(obj);
    data->func();
}

void Thread::start() {
    start_ = true;
    Data *data =  new Data(&tid_, &pid_, func_, name_);
    if (pthread_create(&tid_, NULL, startThread, data)) {
        start_ = false;
        printf("thread : %lud start error\n", tid_);
        delete data;
    } else {
        start_ = true;
        printf("thread : %lud start success\n", tid_);
        //latch_.wait();
    }
}

int Thread::join() {
    join_ = true;
    return pthread_join(pid_, NULL);
}

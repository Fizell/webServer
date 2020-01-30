//
// Created by parallels on 2020/1/20.
//

#include <unistd.h>
#include "Thread.h"
Thread::Thread(Thread::func _func, std::string name) : func_(_func), name_(name), start_(0), join_(0), mutex_(), cond_(mutex_) {}

Thread::~Thread() {
    if (start_ && !join_) pthread_detach(tid_);
}

//为了保存线程名字等信息,由于线程必须传入静态的函数，静态函数不属于对象所以对象无法保存信息
// ,在此另辟蹊径，使用一个单独struct集合保存必要信息
struct Data {
    pthread_t *tid;
    pid_t  *pid;
    std::function<void()> func;
    std::string name;
    Condition cond;
    MutexLock mutex;
    Data(pthread_t *tid, pid_t *pid, std::function<void()> func, std::string name) :
    tid(tid), pid(pid), func(func), name(name), mutex(), cond(mutex)
    {}

};

void *startThread(void *obj) {

    Data *data = static_cast<Data*>(obj);
    //data->cond.wait();
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
        //data->cond.notify();
        printf("thread : %lud start success\n", tid_);
    }

}

int Thread::join() {
    join_ = true;
    return pthread_join(pid_, NULL);
}

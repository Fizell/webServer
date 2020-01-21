//
// Created by parallels on 2020/1/20.
//

#ifndef WEB_SERVER1_1_THREAD_H
#define WEB_SERVER1_1_THREAD_H


#include <sys/types.h>
#include <functional>
#include <string>
#include <pthread.h>
class Thread {
public:
    typedef std::function<void()> func;
    Thread(func _func, std::string name);
    ~Thread();
    void start();
    int join();
private:
    func func_;
    bool start_;
    bool join_;
    pthread_t tid_;
    pid_t pid_;
    std::string name_;

};


#endif //WEB_SERVER1_1_THREAD_H

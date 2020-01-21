//
// Created by parallels on 2020/1/21.
//

#ifndef WEB_SERVER1_1_MUTEXLOCK_H
#define WEB_SERVER1_1_MUTEXLOCK_H


#include <pthread.h>
#include <cstdio>


class MutexLock {
public:
    MutexLock() { pthread_mutex_init(&mutex, NULL); }
    ~MutexLock() {
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }
    void lock() { pthread_mutex_lock(&mutex); }
    void unlock() { pthread_mutex_unlock(&mutex); }
    pthread_mutex_t *get() { return &mutex; }

private:
    pthread_mutex_t mutex;

    // 友元类不受访问权限影响
private:
    friend class Condition;
};

class MutexLockGuard {
public:
    explicit MutexLockGuard(MutexLock &_mutex) : mutex(_mutex) { mutex.lock(); }
    ~MutexLockGuard() { mutex.unlock(); }

private:
    MutexLock &mutex;
};


#endif //WEB_SERVER1_1_MUTEXLOCK_H

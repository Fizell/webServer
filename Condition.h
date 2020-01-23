//
// Created by parallels on 2020/1/21.
//

#ifndef WEB_SERVER1_1_CONDITION_H
#define WEB_SERVER1_1_CONDITION_H

#include <errno.h>
#include <pthread.h>
#include <pthread.h>
#include <time.h>
#include <cstdint>
#include "MutexLock.h"


class Condition {
public:
    explicit Condition(MutexLock &_mutex) : mutex(_mutex) {
        pthread_cond_init(&cond, NULL);
    }
    ~Condition() { pthread_cond_destroy(&cond); }
    void wait() { pthread_cond_wait(&cond, mutex.get());
    printf("wait\n"); fflush(stdout);}
    int notify() { return pthread_cond_signal(&cond); }
    void notifyAll() { pthread_cond_broadcast(&cond); }
    bool waitForSeconds(int seconds) {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);
    }

private:
    MutexLock &mutex;
    pthread_cond_t cond;
};

#endif //WEB_SERVER1_1_CONDITION_H

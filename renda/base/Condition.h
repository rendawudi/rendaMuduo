//
// Created by rhp on 18-12-5.
//

#ifndef RENDA_CONDITION_H
#define RENDA_CONDITION_H

#include "noncopyable.h"
#include "Mutex.h"
namespace renda
{
class Condition : noncopyable
{
public:
    explicit Condition(Mutex &mutex)
        : mutex_(mutex)
    {
        MCHECK(pthread_cond_init(&pcond_, NULL));
    }

    ~Condition()
    {
        MCHECK(pthread_cond_destroy(&pcond_));
    }

    void wait()
    {
        Mutex::UnassignGuard unassignGuard(mutex_);
        MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
    }

    bool waitForSeconds(double seconds);

    void notify()
    {
        MCHECK(pthread_cond_signal(&pcond_));
    }

    void notifyAll()
    {
        MCHECK(pthread_cond_broadcast(&pcond_));
    }

private:
    Mutex& mutex_;
    pthread_cond_t pcond_;
};
}

#endif //RENDA_CONDITION_H

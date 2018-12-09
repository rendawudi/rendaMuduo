//
// Created by rhp on 18-12-6.
//

#ifndef RENDA_THREAD_H
#define RENDA_THREAD_H

#include <functional>
#include "noncopyable.h"
#include "types.h"
#include "Condition.h"
#include "CountDownLatch.h"
#include "Atomic.h"

namespace renda
{
class Thread : noncopyable
{
public:
    typedef std::function<void ()> ThreadFunc;

    Thread(ThreadFunc func, const string& = string());

    ~Thread();

    void start();
    int join();

    bool isStarted()
    {
        return started_;
    }

    pid_t tid()
    {
        return tid_;
    }

    const string& name()
    {
        return name_;
    }

    static int numCreated()
    {
        return numCreated_.get();
    }

private:
    bool joined_;
    bool started_;
    CountDownLatch latch_;
    ThreadFunc func_;
    pid_t tid_;
    pthread_t pthreadId_;
    string name_;

    static AtomicInt64 numCreated_;
};
}


#endif //RENDA_THREAD_H

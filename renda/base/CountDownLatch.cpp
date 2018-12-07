//
// Created by rhp on 18-12-6.
//

#include "CountDownLatch.h"
renda::CountDownLatch::CountDownLatch(int count)
    : mutex_(),
      condition_(mutex_),
      count_(count)
{}

void renda::CountDownLatch::wait()
{
    MutexGuard mutexGuard(mutex_);
    while (count_ > 0)
    {
        condition_.wait();
    }
}

void renda::CountDownLatch::countDown()
{
    MutexGuard mutexGuard(mutex_);
    --count_;
    if (count_ == 0)
    {
        condition_.notifyAll();
    }
}

int renda::CountDownLatch::getCount() const
{
    MutexGuard mutexGuard(mutex_);
    return count_;
}

//
// Created by rhp on 18-12-6.
//

#ifndef RENDA_COUNTDOWNLATCH_H
#define RENDA_COUNTDOWNLATCH_H

#include "Mutex.h"
#include "noncopyable.h"
#include "Condition.h"

namespace renda
{
class CountDownLatch : noncopyable
{
public:
    explicit CountDownLatch(int count) ;
    void wait();
    void countDown();
    int getCount() const;

private:
    mutable Mutex mutex_;
    Condition condition_ GUARDED_BY(mutex_);
    int count_ GUARDED_BY(mutex_);
};
}

#endif //RENDA_COUNTDOWNLATCH_H

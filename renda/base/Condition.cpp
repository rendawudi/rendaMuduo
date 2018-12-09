//
// Created by rhp on 18-12-5.
//

#include "Condition.h"
bool renda::Condition::waitForSeconds(double seconds)
{
    timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);

    const int64_t kNanoSecondsPerSecond = 1000000000;
    int64_t nanSeconds = static_cast<int64_t >(seconds * kNanoSecondsPerSecond);

    abstime.tv_sec += static_cast<time_t >((nanSeconds + abstime.tv_nsec) / kNanoSecondsPerSecond);
    abstime.tv_nsec = static_cast<long > ((nanSeconds + abstime.tv_nsec) % kNanoSecondsPerSecond);

    Mutex::UnassignGuard guard(mutex_);
    MCHECK(pthread_cond_timedwait(&pcond_, mutex_.getPthreadMutex(), &abstime));
}

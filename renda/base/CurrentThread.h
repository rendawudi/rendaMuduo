//
// Created by rhp on 18-12-5.
//

#ifndef RENDA_CURRENTTHREAD_H
#define RENDA_CURRENTTHREAD_H

#include "types.h"

namespace renda
{
namespace CurrentThread
{
    extern __thread int t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLen;
    extern __thread char* t_threadName;

    void cacheTid();

    inline int tid()
    {
        if (__builtin_expect(t_cachedTid == 0, 0))
        {
            cacheTid();
        }
        return t_cachedTid;
    }

    inline const char* tidString()
    {
        return t_tidString;
    }

    inline int tidStringLength()
    {
        return t_tidStringLen;
    }

    inline const char* threadName()
    {
        return t_threadName;
    }

    bool isMainThread();

    void threadSleepUsec(int64_t usec);

    string stackTrace(bool damangle);
}
}

#endif //RENDA_CURRENTTHREAD_H

//
// Created by ubuntu on 18-12-3.
//


#include "TimeStamp.h"
#include <inttypes.h>
#include <sys/time.h>

using namespace renda;

static_assert(sizeof(TimeStamp) == sizeof(int64_t),
                "TimeStamp is the same as int64_t");

string TimeStamp::toString() const
{
    char buf[32] = {};
    int64_t seconds = microsecondsSinceEpoch_ / kMicrosecondsPerSecond;
    int64_t microsenconds = microSencondsSinceEpoch() % kMicrosecondsPerSecond;
    snprintf(buf, sizeof(buf) - 1, "%" PRId64 ".%06" PRId64 " ", seconds, microsenconds);
    return buf;
}

string TimeStamp::toFormattedString(bool showMicrosenconds) const
{
    char buf[64] = {};
    tm tm_time;
    time_t seconds = static_cast<time_t > (microsecondsSinceEpoch_ / kMicrosecondsPerSecond);
    gmtime_r(&seconds, &tm_time);

    if (showMicrosenconds)
    {
        int microSeconds = static_cast<int>(microsecondsSinceEpoch_ % kMicrosecondsPerSecond);
        snprintf(buf, sizeof(buf) - 1, "%4d-%02d-%-2d %02d:%02d:%02d.%06d",
            tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
            tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, microSeconds);
    }
    else
    {
        snprintf(buf, sizeof(buf) - 1, "%4d-%02d-%-2d %02d:%02d:%02d",
                 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }
    return buf;
}

TimeStamp TimeStamp::now()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return TimeStamp(tv.tv_sec * kMicrosecondsPerSecond + tv.tv_usec);
}
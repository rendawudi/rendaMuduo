//
// Created by ubuntu on 18-12-3.
//


#include "TimeStamp.h"
#include <inttypes.h>

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

}
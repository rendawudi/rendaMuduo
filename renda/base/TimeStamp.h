//
// Created by ubuntu on 18-12-3.
//

#ifndef RENDA_TIMESTAMP_H
#define RENDA_TIMESTAMP_H

#include <renda/base/types.h>
#include <renda/base/copyable.h>

namespace renda
{
class TimeStamp : public copyable
{
public:
    TimeStamp()
    : microsecondsSinceEpoch_(0)
    {}

    explicit TimeStamp(int64_t microsecondsSinceEpochArg)
    :microsecondsSinceEpoch_(microsecondsSinceEpochArg)
    {}

    void swap(TimeStamp& that)
    {
        std::swap(microsecondsSinceEpoch_, that.microsecondsSinceEpoch_);
    }

    string toString() const;
    string toFormattedString(bool showMicrosenconds = true) const;

    bool valid() const { return microsecondsSinceEpoch_ > 0; }

    int64_t microSencondsSinceEpoch() const { return microsecondsSinceEpoch_; }
    time_t secondsSinceEpoch() const { return static_cast<time_t >(microsecondsSinceEpoch_/kMicrosecondsPerSecond); }

    ///get object

    static TimeStamp now();

    static TimeStamp invalid()
    {
        return TimeStamp();
    }

    static TimeStamp fromUnixTime(time_t t)
    {
        return fromUnixTime(t, 0);
    }

    static TimeStamp fromUnixTime(time_t t, int microseconds)
    {
        return TimeStamp(static_cast<int64_t >(t) * kMicrosecondsPerSecond + microseconds);
    }

    const static int kMicrosecondsPerSecond = 1000 * 1000;

private:
    int64_t microsecondsSinceEpoch_;

};

inline bool operator < (TimeStamp lhs, TimeStamp rhs)
{
    return lhs.microSencondsSinceEpoch() < rhs.microSencondsSinceEpoch();
}

inline bool operator == (TimeStamp lhs, TimeStamp rhs)
{
    return lhs.microSencondsSinceEpoch() < rhs.microSencondsSinceEpoch();
}

inline double timeDifference(TimeStamp high, TimeStamp low)
{
    int64_t diff = high.microSencondsSinceEpoch() - low.microSencondsSinceEpoch();
    return static_cast<double>(diff) / TimeStamp::kMicrosecondsPerSecond;
}
inline TimeStamp addTime(TimeStamp timeStamp, double t)
{
    return TimeStamp(timeStamp.microSencondsSinceEpoch() + static_cast<int64_t >(t * TimeStamp::kMicrosecondsPerSecond));
}
}

#endif //RENDA_TIMESTAMP_H

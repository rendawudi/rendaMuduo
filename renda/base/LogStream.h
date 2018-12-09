//
// Created by rhp on 18-12-7.
//

#ifndef RENDA_LOGSTREAM_H
#define RENDA_LOGSTREAM_H

#include <functional>

#include "types.h"
#include "noncopyable.h"
#include "StringPiece.h"
namespace renda
{
namespace details
{
const int kSmallBuffer = 4000;

const int kLargeBuffer = kSmallBuffer * 1000;

template<int SIZE>
class FixedBuffer: noncopyable
{
public:
    typedef std::function<void()> CookieFunc;

    FixedBuffer()
        : cur_(data_)
    {
        setCookieFunc(cookieStart);
    }

    ~FixedBuffer()
    {
        setCookieFunc(cookieEnd);
    }

    void append(const char *buf, size_t len)
    {
        // FIXME : 实现部分缓存
        if (avail() > len)
        {
            memcpy(cur_, buf, len);
            add(len);
        }
    }

    int length() const
    {
        return static_cast<int> (cur_ - data_);
    }

    const char *data() const
    {
        return data_;
    }

    char *currentPtr()
    {
        return cur_;
    }

    int avail() const
    {
        return static_cast<int >( sizeof(data_) - length());
    }

    string toString() const
    {
        return string(data_, length());
    }

    StringPiece toStringPiece() const
    {
        return StringPiece(data_, length());
    }

    void add(size_t len)
    {
        cur_ += len;
    }

    void reset()
    {
        cur_ = data_;
    }

    void bzero()
    {
        memZero(data_, sizeof(data_));
    }

    void setCookieFunc(CookieFunc func)
    {
        cookie_ = func;
    }
private:
    const char *end() const
    {
        return data_ + sizeof(data_);
    }

    static void cookieStart();
    static void cookieEnd();

    char *cur_;
    char data_[SIZE];
    CookieFunc cookie_;

};
}
}

#endif //RENDA_LOGSTREAM_H

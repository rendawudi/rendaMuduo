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

size_t convertHex(char buf[], uintptr_t value);


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

class Fmt;

class LogStream : noncopyable
{
    typedef LogStream& self;
public:
    typedef details::FixedBuffer<details::kSmallBuffer> Buffer;

    self operator <<(bool v)
    {
       buffer_.append(v ? "1" : "0" , 1);
        return *this;
    }

    self operator <<(int x)
    {
        formatInteger(x);
        return *this;
    }
    self operator <<(uint x)
    {
        formatInteger(x);
        return *this;
    }
    self operator <<(short x)
    {
        *this << static_cast<int>(x);
        return *this;
    }
    self operator <<(ushort x)
    {
        *this << static_cast<uint >(x);
        return *this;
    }
    self operator <<(long x)
    {
        formatInteger(x);
        return *this;
    }
    self operator <<(ulong x)
    {
        formatInteger(x);
        return *this;
    }
    self operator <<(long long x)
    {
        formatInteger(x);
        return *this;
    }
    self operator <<(unsigned long long x)
    {
        formatInteger(x);
        return *this;
    }
    self operator <<(const void * x)
    {
        uintptr_t i = reinterpret_cast<uintptr_t >(x);
        if (buffer_.avail() > kMaxNumberSize)
        {
            char* buf = buffer_.currentPtr();
            buf[0] = '0';
            buf[1] = 'x';
            int len = details::convertHex(buf, i);
            buffer_.add(len + 2);
        }
    }

    self operator <<(float v)
    {
        *this << static_cast<double >(v);
    }

    self operator <<(double);

    self operator <<(const char* str)
    {
        if (str)
            buffer_.append(str, sizeof(str));
        else
            buffer_.append("NULL char Ptr", 14);
    }

    self operator <<(const unsigned char* str)
    {
        *this << reinterpret_cast<const char*>(str);
    }

    self operator <<(const string& str)
    {
        buffer_.append(str.c_str(), str.size());
        return *this;
    }

    self operator <<(const StringPiece& str)
    {
        buffer_.append(str.data(), str.size());
        return *this;
    }

    self operator <<(const Buffer& buffer)
    {
        *this << buffer.toStringPiece();
        return *this;
    }


    void append(const char* data, int len)
    {
        buffer_.append(data, len);
    }

    const Buffer& buffer()
    {
        return buffer_;
    }

    void resetBuffer()
    {
        buffer_.reset();
    }

private:
    void staticCheck();
    template <typename T>
    void formatInteger(T);

    static const int kMaxNumberSize = 32;

    Buffer buffer_;
};

class Fmt
{
public:
    template <typename T>
    Fmt(const char* fmt, T val);

    const char* data() const
    {
        return buf_;
    }

    int length() const
    {
        return len_;
    }

private:
    char buf_[32];
    int len_;
};
inline LogStream& operator << (LogStream& logStream, const Fmt& fmt)
{
    logStream.append(fmt.data(), fmt.length());
    return logStream;
}
}


#endif //RENDA_LOGSTREAM_H

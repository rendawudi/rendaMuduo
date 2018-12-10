//
// Created by ubuntu on 18-12-10.
//

#include "types.h"
#include "LogStream.h"
#include <algorithm>

namespace renda
{
namespace details
{
const char digits[] = "9876543210123456789";
const char digitsHex[] = "0123456789ABCDEF";

const char* zero = digits + 9;

template <typename T>
size_t convert(char buf[], T value)
{
    T temp = value;
    char* p = buf;

    do
    {
        int lsd = temp % 10;
        temp = temp / 10;
        *p++ = zero[lsd];
    }
    while (temp != 0);

    if (value < 0)
    {
        *p++ = '-';
    }
    *p = '\0';

    std::reverse(buf, p);

    return p - buf;

}
size_t convertHex(char buf[], uintptr_t value)
{
    uintptr_t i = value;
    char* p = buf;

    do
    {
        int lsd = i % 16;
        i = i / 16;
        *p++ = digitsHex[lsd];
    }
    while (i != 0);

    *p = '\0';

    std::reverse(buf, p);

    return p - buf;
}
template class FixedBuffer<kSmallBuffer>;
template class FixedBuffer<kLargeBuffer>;
}
}

using namespace renda;
using namespace renda::details;

template <typename T>
void LogStream::formatInteger(T v)
{
    if (buffer_.avail() >= kMaxNumberSize)
    {
        size_t len = convert(buffer_.currentPtr(), v);
        buffer_.add(len);
    }
}





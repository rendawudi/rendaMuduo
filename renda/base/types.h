//
// Created by ubuntu on 18-12-3.
//

#ifndef RENDA_TYPES_H
#define RENDA_TYPES_H

#ifndef NDEBUG
#include <assert.h>
#endif

#include <stdint.h>
#include <string>
#include <string.h>
namespace renda
{
    using std::string;

    inline void memZero(void* p, size_t n)
    {
        memset(p, 0, n);
    }

    template <typename To, typename From>
    inline To implicit_cast(From const &f)
    {
        return f;
    }

    template <typename To, typename From>
    inline To down_cast(From &f)
    {
#if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTI)
        assert(f == nullptr || dynamic_cast<To>(f) != nullptr);
#endif
        return static_cast<To>(f);
    }
}

#endif //RENDA_TYPES_H

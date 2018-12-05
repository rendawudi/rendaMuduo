//
// Created by rhp on 18-12-5.
//

#ifndef RENDA_ATOMIC_H
#define RENDA_ATOMIC_H

#include "types.h"
#include "noncopyable.h"

namespace renda
{
namespace details
{

template <typename T>
class AtomicIntegerT : noncopyable
{
public:
    AtomicIntegerT()
        : value(0)
    {}

    T get()
    {
        return __sync_val_compare_and_swap(&value, 0, 0);
    }

    T getAndAdd(T x)
    {
        return __syn_fetch_and_add(&value, x);
    }

    T addAndGet(T x)
    {
        return getAndAdd(x) + x;
    }

    T incrementAndGet()
    {
        return addAndGet(1);
    }

    T decrementAndGet()
    {
        return addAndGet(-1);
    }

    T getAndSet(T newValue)
    {
        return __syn_test_and_set(&value, newValue);
    }

private:
    T value;
};
}

typedef details::AtomicIntegerT<int32_t > AtomicInt32;
typedef details::AtomicIntegerT<int64_t > AtomicInt64;

}

#endif //RENDA_ATOMIC_H

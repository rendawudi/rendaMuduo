//
// Created by rhp on 18-12-6.
//

#ifndef RENDA_EXCEPTION_H
#define RENDA_EXCEPTION_H

#include "types.h"
#include <bits/exception.h>
namespace renda
{
class Exception: std::exception
{
public:
    Exception(string what);
    ~Exception() noexcept override = default;

    const char *what() const noexcept override
    {
        return message_.c_str();
    }

    const char *stackTrace() const noexcept
    {
        return stack_.c_str();
    }

private:
    string message_;
    string stack_;
};
}

#endif //RENDA_EXCEPTION_H

//
// Created by rhp on 18-12-7.
//

#ifndef RENDA_STRINGPIECE_H
#define RENDA_STRINGPIECE_H

#include <string_view>
#include "types.h"

namespace renda
{
class StringArg
{
public:
    StringArg(const char* str)
    :str_(str)
    {}

    StringArg(const string &str)
    :str_(str.c_str())
    {}

    const char* c_str()
    {
        return str_;
    }

private:
    const char* str_;
};

typedef std::string_view StringPiece;

}

#endif //RENDA_STRINGPIECE_H

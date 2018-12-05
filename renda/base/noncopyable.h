//
// Created by rhp on 18-12-5.
//

#ifndef RENDA_NONCOPYABLE_H
#define RENDA_NONCOPYABLE_H


class noncopyable
{
protected:
    noncopyable() = default;
    ~noncopyable() = default;
public:
    noncopyable(const noncopyable&) = delete;
    void operator = (const noncopyable&) = delete;
    
};

#endif //RENDA_NONCOPYABLE_H

//
// Created by rhp on 18-12-6.
//

#include "Exception.h"
namespace renda
{
Exception::Exception(std::string what)
    : message_(std::move(what)),
      stack_(CurrentThread::stackTrace(false))
{

}
}

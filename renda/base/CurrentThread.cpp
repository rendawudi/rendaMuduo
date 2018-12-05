//
// Created by rhp on 18-12-5.
//

#include <execinfo.h>
#include <cxxabi.h>
#include "CurrentThread.h"

namespace renda
{
namespace CurrentThread
{
__thread int t_cachedTid = 0;

__thread char t_tidString[32];

__thread int t_tidStringLen = 6;

__thread char *t_threadName = "unknown";

string stackTrace(bool damangle)
{
    const int max_frames = 200;
    void* stackStrs[max_frames];
    int nptrs = ::backtrace(stackStrs, max_frames);
    char** strings = ::backtrace_symbols(stackStrs, nptrs);
    string stack;
    if (strings)
    {
        size_t len = 256;
        char* demangled = damangle ? static_cast<char*>(::malloc(len)) : nullptr;
        for (int i = 1; i < nptrs; ++i)  // skipping the 0-th, which is this function
        {
            if (damangle)
            {
                // https://panthema.net/2008/0901-stacktrace-demangled/
                // bin/exception_test(_ZN3Bar4testEv+0x79) [0x401909]
                char* left_par = nullptr;
                char* plus = nullptr;
                for (char* p = strings[i]; *p; ++p)
                {
                    if (*p == '(')
                        left_par = p;
                    else if (*p == '+')
                        plus = p;
                }

                if (left_par && plus)
                {
                    *plus = '\0';
                    int status = 0;
                    char* ret = abi::__cxa_demangle(left_par+1, demangled, &len, &status);
                    *plus = '+';
                    if (status == 0)
                    {
                        demangled = ret;  // ret could be realloc()
                        stack.append(strings[i], left_par+1);
                        stack.append(demangled);
                        stack.append(plus);
                        stack.push_back('\n');
                        continue;
                    }
                }
            }
            // Fallback to mangled names
            stack.append(strings[i]);
            stack.push_back('\n');
        }
        free(demangled);
        free(strings);
    }
    return stack;
}
}
}

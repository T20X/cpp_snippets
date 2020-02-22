#pragma once

#include <iostream>
#include <string.h>
#include <errno.h>

namespace utils
{
    static void report()
    {
        int errorCode = errno;
        std::cerr << errorCode << ": " << strerror(errorCode) << "\n";
        throw std::runtime_error(strerror(errorCode));
    }
}
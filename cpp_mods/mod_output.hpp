#ifndef MOD_OUTPUT
#define MOD_OUTPUT

#include "std_headers.hpp"

namespace mod 
{
    void print() {}

    template<typename T, typename... Types>
    void print(const T& first, const Types&... rest) {
        cout << first << " ";
        print(rest...);
    }
}

#endif
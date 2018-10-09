#ifndef MOD_STRING
#define MOD_STRING
#include "mod_macros.hpp"

namespace mod 
{
    template<class T>
    string toString(T data) {
        ostringstream oss;
        oss << data;
        return oss.str();
    }

    template<class T>
    string join(const vector<T> &items, const string separator = ", ") {
        ostringstream oss;
        int n = items.size();
        repeat(i, n) {
            oss << items[i];
            if ( i != n - 1 )
                oss << separator;
        }
        return oss.str();
    }

    string concat() { return ""; }

    template<class T, class... Types>
    string concat(const T &first, const Types&... rest) {
        return toString(first) + concat(rest...);
    }
}
#endif
#ifndef MOD_UTILITY
#define MOD_UTILITY
#include "mod_macros.hpp"
#include "mod_string.hpp"

#define LAYER 2

namespace mod
{

    template <class A, class B> class couple;
    template <class A, class B> ostream& operator<<(ostream&, const couple<A, B>&);
    template<class A, class B> 
    struct couple {
        // Improvement over std::pair in simplicity.
        // I believe that STL is not at all extendable. 
        A first;
        B second;

        couple() {}

        couple(A first, B second): first(first), second(second)
        {}

        friend ostream& operator<< <A, B> (ostream &os, const couple<A, B> &c);

    };
    template<class A, class B>
    ostream& operator<<(ostream &os, const couple<A,B> &c) {
        os << concat("( ", c.first, ", ", c.second, " )");
        return os;
    }

} // mod
#endif
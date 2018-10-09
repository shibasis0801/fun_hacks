#ifndef MOD_MATRIX
#define MOD_MATRIX
#include "mod_macros.hpp"

namespace mod
{
    template<class C>
    vector<vector<C>> Matrix(int rows, int cols, C default_value) {
        return vector<vector<C>>(rows, vector<C>(cols, default_value));
    }

    template<class C>
    vector<vector<C>> Matrix(int rows, int cols) {
        return vector<vector<C>>(rows, vector<C>(cols));
    }
} // mod
#endif
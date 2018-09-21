#ifndef MOD_VECTOR
#define MOD_VECTOR
#include "std_headers.hpp"

namespace mod {
    template<class T>
    vector<T> join(const vector<vector<T>> &items) {
        vector<T> flatten;
        for (const auto &vec : items) {
            for (auto item : vec) {
                flatten.push_back(item);
            }
        }
        return std::move(flatten);
    }

    template<class T>
    vector<T> join(const initializer_list<vector<T>> &items) {
        vector<T> flatten;
        for (const auto &vec : items) {
            for (auto item : vec) {
                flatten.push_back(item);
            }
        }
        return std::move(flatten);
    }
}
#endif
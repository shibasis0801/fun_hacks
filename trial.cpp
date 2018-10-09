
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <set>
using namespace std;

#define repeat(i, n) for ( int i = 0; i < n; ++i )
#define inverse_for(i, n) for ( int i = n; i >= 0; --i )

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
}
namespace mod 
{
    void print() {}

    template<typename T, typename... Types>
    void print(const T& first, const Types&... rest) {
        cout << first << " ";
        print(rest...);
    }
}
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

        couple(){}
        couple(A first, B second): first(first), second(second)
        {}

        friend ostream& operator<< <A, B> (ostream &os, const couple<A, B> &c);

    };
    template<class A, class B>
    ostream& operator<<(ostream &os, const couple<A,B> &c) {
        os << concat("( ", c.first, ", ", c.second, " )");
        return os;
    }

}

using namespace mod;

template <class T>
struct matrix {

    vector<vector<T>> data;

    matrix(int rows, int cols) : 
        data(vector<vector<T>>(rows, vector<T>(cols)))
    {}

    matrix(int rows, int cols, T default_value) : 
        data(vector<vector<T>>(rows, vector<T>(cols, default_value)))
    {}

    matrix(int rows, int cols, const function<T(int, int)> &fn) {
        data = std::move(vector<vector<T>>(rows, vector<T>(cols)));
        repeat(row, rows)
            repeat(col, cols)
                data[row][col] = fn(row, col);
    }

    couple<int, int> size() {
        
        int rows = data.size();
        int cols = 0;

        if ( ! data.empty() )
            if ( !data[0].empty() )
                cols = data[0].size();

        return {rows, cols};
    }

    vector<T> operator[](const int &row) {
        if (row < data.size())
            return data[row];
        else    
            return vector<T>();
    }

    vector<reference_wrapper<T>> operator()(const int &col) {
        auto [rows, cols] = size();
        if ( col < cols ) {

            vector<reference_wrapper<T>> colomn;
            
            repeat(row, rows) 
                colomn.push_back(reference_wrapper<T>(data[row][col]));

            return colomn;
        }
        else
            return vector<reference_wrapper<T>>();
    }
};

namespace algebra 
{
    matrix<int> 
    I_matrix(int size) {
        return matrix<int>(size, size, [=](int row,int col) {
            return (row == col) ? 1 : 0;
        });
    }

    matrix<int>
    ap_matrix(int rows, int cols, int start = 1, int step = 1) {
        return matrix<int>(rows, cols, [=](int row, int col) {
            int n = row * cols + col + 1;
            return start + (n - 1) * step;
        });
    }

    matrix<long double>
    gp_matrix(int rows, int cols, long double a = 1, long double r = 2) {
        return matrix<long double>(rows, cols, [=](int row, int col) {
            int n = row * cols + col + 1;
            return a * pow(r, n - 1);
        });
    }

    
}

using namespace algebra;

int main() {
    couple<string, int> a("shibasis",81);
    cout << a << '\n';


    matrix<int> m(3, 4, [](int row, int col) {
        return 4 * row + col + 1; 
    });


    auto I = gp_matrix(3, 3, 1, 2);
    repeat(i, 3) {
        repeat(j, 3)
            cout << I[i][j];
        cout << '\n';
    }

    auto col_3 = m(3);
    col_3[0].get() = 999;
    cout << col_3[0];


    auto [rows, cols] = m.size();
    repeat(row, rows) {
        repeat(col, cols)   
            cout << m[row][col] << ' ';
        cout << '\n';
    }

}
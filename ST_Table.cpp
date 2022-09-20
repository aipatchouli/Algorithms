#include<bits/stdc++.h>
using namespace std;

/*
Spares Table 静态 Range Minimum/Maximum Query
*/
// F[i, j] = min/max(F[i, j-1], F[i+2^(j-1), j-1])
// 区间长度为 2^j, 从 i 开始, 2^j 个数
// 数组长度为n, 最大区间长度为 2^k, k = log2(n)

template <typename T>
class SparseTable {
private:
    using VT = vector<T>;
    using VVT = vector<VT>;
    // 函数指针 template<typename R, typename Arg0> class myfunction<R(Arg0)> {}
    using func_type = function<T(const T&, const T&)>; 
    
    VVT ST;

    static T default_func(const T& t1, const T& t2) {return max(t1, t2)};

    func_type op;

public:
    SparseTable <T> (const vector<T> &v, func_type _func = default_func) {
        op = _func;
        int len = v.size(), k = ceil(log2(len)) + 1;  //向上取整
        ST.assign(len, VT(k, 0));
        for (int i = 0; i < len; ++i) {
            ST[i][0] = v[i];
        }
        for (int j = 1; j < k; ++j) {
            int pj = (1 << (j - 1)); // 2^j
            for (int i = 0; i < len - pj; ++i) {
                ST[i][j] = op(ST[i][j-1], ST[i + pj][j-1]);
            }
        }
    }

    T query(int l, int r) {
        int lt = r - l + 1;
        int q = ceil(log2(lt)) - 1;
        return op(ST[l][q], ST[r - (1 << q) + 1][q]);
    }
};
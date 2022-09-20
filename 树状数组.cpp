#include<bits/stdc++.h>
using namespace std;
/* 
简单求区间和，用「前缀和」
多次区间修改，用「线段树」
其他情况，用「树状数组」（Binary Indexed Tree）
*/

/* 
树状数组核心：（下标从 1 开始）i 位置 保存的范围是 i 二进制 末尾 0 的个数
以 前缀和 为例
1101 = 13； 查询 前 13 个数的 前缀和 需要

1101 = 13  逐渐减去最后一个一 ，不能为 0 ，因为下标从 1 开始
1100 = 12
1000 = 8

13 12 8 这几个位置加起来 就是 前 13 个数的 前缀和

同样
修改 是在 最后一个一 的位置 加 1
修改 13 位置
1101 = 13

需要修改
1101 = 13
1110 = 14
10000 = 16 注意不能越界
*/

// 
class BinaryIndexTree {
private:
    vector<int> tree;
    int size;
public: 
    BinaryIndexTree(int n) : tree(n+1), size(n+1) {}

    int lowbit(int x) {
        return x & (-x);
    }

    int query(int x) {
        int sum = 0;
        while (x > 0) {
            sum += tree[x];
            x -= lowbit(x);
        }
        return sum;
    }

    void add(int x, int val) {
        while (x < size) {
            tree[x] += val;
            x += lowbit(x);
        }
    }
};

vector<int> Discretization(vector<int>& arr) {
    vector<int> pseudo = arr;
    sort(pseudo.begin(), pseudo.end());
    pseudo.erase(unique(pseudo.begin(), pseudo.end()), pseudo.end());
    
    return pseudo;
}

int find(vector<int>& arr, int x) {
    int l = 0, r = arr.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (arr[mid] >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return r + 1;    // 映射的下标从1开始
}



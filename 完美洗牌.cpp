#include<bits/stdc++.h>
using namespace std;

// https://wizardforcel.gitbooks.io/the-art-of-programming-by-july/content/02.09.html
// 有个长度为2n的数组{a1,a2,a3,...,an,b1,b2,b3,...,bn}，希望排序后{a1,b1,a2,b2,....,an,bn} / {b1,a1,b2,a2,...bn,an}，请考虑有无时间复杂度o(n)，空间复杂度0(1)的解法

// 再综合到任意情况，任意的第i个元素，最终换到了 (2 i) % (2 n + 1)的位置

// 对于 2*n = （3^k-1）这种长度的数组，恰好只有k个圈，且每个圈头部的起始位置分别是1,3,9，...3^(k-1)
// 让一部分的长度m(其中m < n)满足结论 2*m = （3^k-1），剩下的n-m部分单独计算
// 原始数组下标：1..m, (m+1.. n)，(n+1 .. n+m), n+m+1,..2*n
// 括号两段 交换位置

//翻转字符串时间复杂度O(to - from)
void reverse(vector<int>& a, int from, int to)
{
    int t;
    for (; from < to; ++from, --to)
    {
        t = a[from];
        a[from] = a[to];
        a[to] = t;
    }
}

//循环右移num位 时间复杂度O(n)
void RightRotate(vector<int>& a, int num, int n)
{
    reverse(a, 1, n - num);
    reverse(a, n - num + 1, n);
    reverse(a, 1, n);
}

// 翻转后，得到的目标数组的下标为：1..m    n+1..n+m    m+1 .. n       n+m+1,..2*n

class Solution
{
    public:
        //对数组a进行洗牌算法,s代表洗牌的首元素，t代表洗牌的尾元素
        void PerfectShuffle(vector<int>& a, int s, int t) {
            if (s > t) return;
            int gap = t - s + 1;
            //判断数组长度是不是3^k-1
            int k = 1, p = 3;
            while (p - 1 <= gap) { k++; p *= 3; }
            //循环右移,确定m,n长度
            int n = gap/2, m = n;
            if (p != gap){
                m = (p / 3 - 1)/2;
                LeftRotate(a, s+m, s+n-1, s+m+n-1);
            }
            //前3^k-1个元素进行环操作
            int start = 1;
            while (--k){
                cycle(a, start, s, 2*m);
                start *= 3;
            }
            //最后剩余进行递归操作
            PerfectShuffle(a, s+2*m, t);
        }
    private:   
        void cycle(vector<int>& a, int s, int begin, int length) {
            int pre = a[begin + s-1];
            int mod = length+1;
            int next = s * 2 % mod;
            while (next != s){
                swap(pre,a[begin+next-1]);
                next = 2 * next % mod;
            }
            a[begin+s-1] = pre;
        }
        
        
        //翻转[s,t]之间的元素
        void Reverse(vector<int>& a, int s, int t) {
            while (s < t) swap(a[s++], a[t--]);
        }
        
        
        //将[s,m]之间的元素循环右移到[m+1,t]之后
        void LeftRotate(vector<int>& a, int s, int m, int t) {
            Reverse(a, s, m);
            Reverse(a, m + 1, t);
            Reverse(a, s, t);
        }
};


int main() {
    int n = 18 / 2;
    vector<int> clutter {1,2,3,4,5,6,7,8,9,100,200,300,400,500,600,700,800,900};
    // PefectShuffle1(clutter, n);
    // for (const auto& x : clutter) {
    //     cout << x << " ";
    // }
    Solution s;
    s.PerfectShuffle(clutter, 0, clutter.size()-1);
    for (const auto& x : clutter) {
        cout << x << " ";
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

//kmp_cur 算法 让 j 从当前 next 值回溯，即 j = next[j]

class Solution {
public:
    void getNext(int* next, const string& s) { // 求 最大相等前后缀字符串长度
        int k, i;			//k->前缀末尾   i->后缀末尾 
        next[0] = -1;		//规定 next[0] = -1
        k = -1; i = 0;		//规定 k 从 -1 开始，因为后面需要给 next[1] 赋值，其实 k 的初始值和 next[0] 是对应的
        while(i < s.size() - 1) { //因为是先++，后赋值
            if (k==-1 || s[k]==s[i]) { // k==-1 i = 0 边界 next[1]一定是0；
                ++k; ++i;
                next[i] = k; //因为k记录这前缀末尾，如果相等，则 ++最大相等前后缀字符串长度，进入比对下一个字符
            } else {
                k = next[k]; //否则 回溯；i是不会动的，k回溯的意思 把前缀当作模式串 把后缀当作主串 kmp 匹配
            }
        }		
    }
    int strStr(string haystack, string needle) {
        int S = haystack.size(), T = needle.size();
        if (T == 0) {
            return 0;
        }
        int next[T];
        getNext(next, needle);
        int i = 0, j = 0;		//i->主串haystack   j->模式串needle
        while (i < S && j < T) 
        {
		    if (j == -1 || haystack[i] == needle[j]) {	//这其实是两个判断语句合成为了一个，拆开后可能更好理解
			    ++i; 
                ++j;
		    } else {
			    j = next[j];			//向前回溯
		    }
	    }
	    if (j >= T) {
            return (i - T);
        } else {
            return -1;	 
        }
    }
};

int main() {
    Solution s;
    string haystack = "hello";
    string needle = "ll";
    int res = s.strStr(haystack, needle);
    cout << res << endl; 
    return 0;
}
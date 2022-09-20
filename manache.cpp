#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.length() == 0) {
			return 0;
		}
        vector<char> str = manacherstring(s);
        vector<int> parr(str.size());
        int c = -1; //当前比较的回文子串的中心
        int r = -1; //当前考虑的比对成功的下一个位置
        int max = INT_MIN;
        int max_int = -1;
        //遍历
        for (int i = 0; i < str.size(); i++) {
            //考虑的是在c，r的范围内估计parr的值
            //1.要么是c中的对称位置的值，并且不能超过c,r的范围；2.要么在外面，为1；
            parr[i] = r > i ? min(parr[2*c-i], r-i) : 1;
            //判断左右越界,或者是否开始赋值c,r范围内的parr值
            while (i+parr[i] < str.size() && i-parr[i] > -1) {
                if (str[i+parr[i]]==str[i-parr[i]]) {
                    parr[i]++;
                } else {
                    break;
                }
            }
            //外扩
            if (i + parr[i] > r) {
                c = i;
                r = i + parr[i];
            }
        if (max <= parr[i]) {
            max = parr[i];
            max_int = i;
        }
            
        }
        string maxsubstr;
        for (int j=max_int-parr[max_int]+1; j<=max_int+parr[max_int]-1; j++) {
            if (str[j] != '#') {
                maxsubstr.push_back(str[j]);
            } 
        }
        return maxsubstr;
    }
    
    vector<char> manacherstring(string& s) {
        vector<char> str;
        str.push_back('#');
        for (const auto& x : s) {
            str.push_back(x);
            str.push_back('#');
        }
        return str;
    }
};
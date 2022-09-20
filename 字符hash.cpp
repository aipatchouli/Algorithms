#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    unsigned long long prime = 31; // 基数
    string longestDupSubstring(string s) {
        n = s.size();
        int l = 1;
        int r = n - 1;
        int pos = -1;
        int len = 0;

        auto find = [&](int len){
            unsigned long long hash = 0;
            unsigned long long power = 1;
            for (int i = 0; i < len; i++) {
                hash = hash * prime + (s[i] - 'a'); // 将字符串转化为 sub[0]*p^{m-1}+sub[1]*p^{m-2}+...+sub[m-1]
                power *= prime; // prime ^ m
            }
            unordered_set<unsigned long long> exist{hash};
            for(int i = len; i < n; i++) {
                hash = hash * prime - power * (s[i-len] - 'a') + (s[i] - 'a');
                if (exist.count(hash)) return (i - len + 1);
                exist.insert(hash);
            }
            return -1;
        };

        while(l <= r) {
            int mid = (l + r) / 2;
            int start = find(mid);
            if (start != -1) {
                len = mid;
                pos = start;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
            cout << s.substr(pos, len) << endl;
        }

        if (pos == -1) return "";
        else return s.substr(pos, len);
    }
};

int main() {
    string s = "ananananan";
    Solution sol;
    cout << sol.longestDupSubstring(s) << endl;
    return 0;
}
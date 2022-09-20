#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int res = 0;
    string tar;
    int numDistinct(string s, string t) {
        int m = s.length(), n = t.length();
        if (m < n) {
            return 0;
        }
        vector<char> chs(s.begin(), s.end());
        tar = t;
        process(chs, 0); //遍历chs
        return res;
    }

    void process(vector<char> chs, int i) {
        if (i == chs.size()) {
            if (compare(chs, tar)) {
                res += 1;
            }
            return;
            // for (const auto& x : chs) {
            //     cout << x;
            // }
        }
        process(chs, i+1);
        char tmp = chs[i];
        chs[i] = 0;
        process(chs, i+1);
        chs[i] = tmp;
    }

    bool compare(vector<char> chs, string str) {
        string sb;
        for (const auto& x : chs) {
            if (x != 0) {
                sb += x;
            }
        }
        if (sb == str) {
            return true;
        } else {return false;}
    }
};

int main() {
    Solution s;
    string str, t;
    getline(cin, str);
    getline(cin, t);
    int results;
    results = s.numDistinct(str, t);
    cout << results << endl;
    return 0;
}

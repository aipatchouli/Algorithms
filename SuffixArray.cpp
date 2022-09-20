#include<bits/stdc++.h>
using namespace std;


class SuffixArray {
private:
    string s;
    int n, w;
    vector<int> sa, rk, oldrk; // sa[i] 表示排名为 i 的后缀的起始位置 rk[i] 表示后缀 s[i..n] 的排名
    // sa[rk[i]] == rk[sa[i]] == i
    // 为了防止访问 rk[i+w] 导致数组越界，开两倍数组。
    // 当然也可以在访问前判断是否越界，但直接开两倍数组方便一些。

    bool cmp(int a, int b) {
        return (oldrk[a] == oldrk[b]) && (oldrk[a + w] == oldrk[b + w]);
    }

    void buildsa() {
        int i, p;
        for (i = 1; i <= n; i++) rk[i] = s[i-1], sa[i] = i;
    
        for (w = 1; w < n; w <<= 1) {
            sort(sa.begin() + 1, sa.begin() + n + 1, [&](int a, int b) {
                return rk[a] == rk[b] ? rk[a + w] < rk[b + w] : rk[a] < rk[b];
            });
            oldrk = rk;
            for (p = 0, i = 1; i <= n; ++i) {
                rk[sa[i]] = cmp(sa[i], sa[i - 1]) ? p : ++p;
            }
        }
    }

public:
    explicit SuffixArray(string& str) {
        s = str;
        n = s.size();
        sa.resize(n + 1);
        rk.resize(n << 1);
        oldrk.resize(n << 1);
        buildsa();
    }

    vector<int> getsa() {
        return vector<int>(sa.begin() + 1, sa.end());
    }
};

/************************************************************************/

class SuffixArrayRadixSort {
private:
    string s;
    int n, w, m;
    vector<int> sa, rk, oldrk, idx, px, cnt;
    // 为了防止访问 rk[i+w] 导致数组越界，开两倍数组。
    // 当然也可以在访问前判断是否越界，但直接开两倍数组方便一些。

    bool cmp(int a, int b) {
        return (oldrk[a] == oldrk[b]) && (oldrk[a + w] == oldrk[b + w]);
    }

    void buildsa() {
        int i, p;
        for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i-1]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

        for (w = 1; ; w <<= 1, m = p) { // m=p 就是优化计数排序值域
            for (p = 0, i = n; i > n - w; --i) idx[++p] = i;
            for (i = 1; i <= n; ++i) if (sa[i] > w) idx[++p] = sa[i] - w;
            // for (i = 0; i <= m; ++i) cnt[i] = 0;
            fill(cnt.begin(), cnt.end(), 0);
            for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[idx[i]]];
            for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
            for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = idx[i];
            for (i = 1; i <= n; ++i) oldrk[i] = rk[i];
            for (p = 0, i = 1; i <= n; ++i) {
                rk[sa[i]] = cmp(sa[i], sa[i - 1]) ? p : ++p;
            }
            if (p == n) {
                for (i = 1; i <= n; ++i) sa[rk[i]] = i;
                break;
            }
        }
    }

public:
    explicit SuffixArrayRadixSort(string& str) {
        s = str;
        n = s.size();
        m = 300;
        sa.resize(n + 1);
        rk.resize(n + 1);
        oldrk.resize(n << 1);
        idx.resize(n + 1);
        px.resize(n + 1);
        cnt.resize(m + 1);
        buildsa();
    }

    vector<int> getsa() {
        return vector<int>(sa.begin() + 1, sa.end());
    }
};

vector<int> getHeight(vector<int>& s, vector<int>& rk) {
    int n = s.size();
    vector<int> height (n+1);
    for (int i = 1, k = 0; i <= n; ++i) {
        if (rk[i] == 0) continue;
        if (k) --k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        height[rk[i]] = k;
    }
    return vector<int>(height.begin() + 1, height.end());
}

int main() {
    string s("tyhrtjygyhgtjykjetyhrtjfgadrfhagdSFDhstrygyjukjthfdgstfhst");
    
    SuffixArrayRadixSort SARS(s);
    for (const auto &i : SARS.getsa()) {
        cout << i << " ";
    }
    cout << endl;
    SuffixArray SA(s);
    for (const auto &i : SA.getsa()) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
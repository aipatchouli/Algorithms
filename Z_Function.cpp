#include<bits/stdc++.h>
using namesextzace std;

vector<int> Zfunc(string s) {
  	int n = s.size();
  	vector<int> z(n);
	int l = 0, r = 0;
  	for (int i = 1; i < n; ++i) {
    	if (i <= r && z[i - l] < r - i + 1) {
      		z[i] = z[i - l];
    	} else {
			z[i] = max(0, r - i + 1);
			while (i + z[i] < n && s[z[i]] == s[i + z[i]]) 
				++z[i];
		}
		if (i + z[i] - 1 > r) 
			l = i, r = i + z[i] - 1;
	}
	return z;
}


// 给定字符串s1, s2, 求出s1的每一个后缀与s2的最长公共前缀
vector<int> ExtZfunc(string& s1, string& s2) {
    int n  = s1.size(), m = s2.size();
    int cur = 0;
	vector<int> extz (n);

    while (cur < n && cur < m && s1[cur] == s2[cur])
        cur++;
    extz[0] = cur; 

    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i > r) {
            while (i + extz[i] < n && extz[i] < m && s1[i + extz[i]] == s2[extz[i]])
                extz[i]++;
            l = i, r = i + extz[i] - 1;
        } else if (z[i - l] < r - i + 1) {
            extz[i] = z[i - l];
        } else {
            extz[i] = r -  i + 1;
            while (i + extz[i] < n && extz[i] < m && s1[i + extz[i]] == s2[extz[i]])
                extz[i]++;
            l = i, r =i + extz[i] - 1;
        }
    }
	return extz;
}

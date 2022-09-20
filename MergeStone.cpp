#include<bits/stdc++.h>
using namespace std;

//石子合并：区间 DP 问题；四边形优化

class Solution_1 {   // dp[i,j] = max/min{dp[i,j], dp[i, k] + dp[k+1, j] + cost}
private:
    int max_val = 99999999; 
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if ((n - 1) % (k - 1) != 0) 
            return -1;
        vector<vector<vector<int>>> dp (n+1, vector<vector<int>>(n+1, vector<int>(k+1, 0)));
        vector<int> sum (n+1);
        for (int i = 1; i <= n; ++i) 
            sum[i] = sum[i - 1] + stones[i - 1];
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                for (int m = 2; m <= k; ++m) dp[i][j][m] = max_val;
            }
            dp[i][i][1] = 0;
        }
        for (int len = 2; len <= n; ++len) { // 枚举区间长度
            for (int i = 1; i + len - 1 <= n; ++i) { // 枚举区间起点
                int j = i + len - 1;
                for (int m = 2; m <= k; ++m) { // 枚举堆数 K = k-1 + 1
                    for (int p = i; p < j; p += k - 1) {  // 枚举分界点
                        dp[i][j][m] = min(dp[i][j][m], dp[i][p][1] + dp[p + 1][j][m - 1]);
                    }
                }
                dp[i][j][1] = dp[i][j][k] + sum[j] - sum[i - 1];
            }
        }
        return dp[1][n][1];
    }
};

// 定义dp[i][j]为尽可能多的合并区间[i, j] 所需的成本，不一定能合并成一堆，但合并完成后剩下的堆数一定小于k，更具体地，剩余的堆数一定是(n - 1) % (k - 1) + 1
// dp[i][j] = min(dp[i][p] + dp[p + 1][j]), i <= p < j，如果可以继续合并，dp[i][j] += sum(i, j)
class Solution_2 {
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if ((n - 1) % (k - 1) != 0) 
            return -1;
        vector<vector<int>> dp (n+1, vector<int>(n+1, 0));
        vector<int> sum (n+1);
        
        for (int i = 1; i <= n; ++i) 
            sum[i] = sum[i - 1] + stones[i - 1];
        for (int len = k; len <= n; ++len) { // 枚举区间长度
            for (int i = 1; i + len - 1 <= n; ++i) { // 枚举区间起点
                int j = i + len - 1;
                dp[i][j] = numeric_limits<int>::max();
                for (int p = i; p < j; p += k - 1) {  // 枚举分界点
                    dp[i][j] = min(dp[i][j], dp[i][p] + dp[p + 1][j]);
                }
                if ((j - i) % (k - 1) == 0) dp[i][j] += sum[j] - sum[i - 1];
            }
        }
        return dp[1][n];
    }
};


int main() {
    vector<int> stone {3,5,1,2,6};
    int k = 3;
    Solution_2 s;
    int res = s.mergeStones(stone, k);
    cout << res << endl;
    
    return 0;
}
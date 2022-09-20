#include<bits/stdc++.h>
using namespace std;


class Solcution_Recursion {
public:
    int change(int amount, vector<int>& coins) {
        return process(coins, 0, amount);
    }

    //都一样
    int process(vector<int>& coins, int index, int rest) {
        if (index==coins.size()) {
            return rest==0 ? 1 : 0;
        }
        int res = 0;
        for (int num = 0; coins[index]*num <= rest; num++) {
            res += process(coins, index+1, rest-coins[index]*num);
        }
        return res;
    }

};



class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int N = coins.size();
        vector<vector<int>> dp (N+1, vector<int>(amount+1));
        dp[N][0] = 1; //题目设定
        for (int rest = 1; rest <= amount; rest++) {
            dp[N][rest] = 0;
        }
        //开始 dp
        for (int index = N-1; index >= 0; index--) {
            for (int rest = 0; rest <= amount; rest++) {
                int res = 0;
                for (int num = 0; coins[index]*num <= rest; num++) {
                    res += dp[index+1][rest-coins[index]*num];
                    //table DP 精髓，将递归中的函数过程替换为 查表，更新 过程
                    //res += process(coins, index+1, rest-coins[index]*num);
                }
                dp[index][rest] = res;
            }
        }
        return dp[0][amount];
    }
};


class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int N = coins.size();
        vector<vector<int>> dp (N+1, vector<int>(amount+1));
        dp[N][0] = 1; //题目设定
        for (int rest = 1; rest <= amount; rest++) {
            dp[N][rest] = 0;
        }
        //开始 dp
        for (int index = N-1; index >= 0; index--) {
            for (int rest = 0; rest <= amount; rest++) {
                dp[index][rest] = dp[index+1][rest];
                if (rest - coins[index] >= 0) {
                    dp[index][rest] += dp[index][rest - coins[index]];
                }
            }
        }
        return dp[0][amount];
    }
};



class Solution_dp {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1);
        dp[0] = 1;
        for (int& coin : coins) {
            for (int i = coin; i <= amount; i++) {
                dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }
};



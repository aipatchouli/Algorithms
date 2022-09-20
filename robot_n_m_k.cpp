/**
 * 假设有排成一行的N个位置，记为1~N，N一定大于或等于2;
 * 开始时机器人在M（1 <= M <= N）位置上，
 * 如果机器人位于1位置，那么下一步只能走到2位置，
 * 如果机器人位于N位置，那么下一步只能走到N-1位置，
 * 如果机器人位于中间的任一位子，那么下一步可以向左走，也可以向右走。
 * 机器人必须走K步，最终来到P（1 <= P <= N），给定参数N，M，K，P，有多少种走法？
 **/

#include<bits/stdc++.h>
using namespace std;

class robot_walk{
public:
    int walk_Recursion(int N, int M, int K, int P) {    // 总共N个格子，目标P，走K步，初始位于M
        return process1_Recursion(N, P, K, M);
    }

    int process1_Recursion(int N, int P, int rest, int cur) {    // 总共N个格子，目标P，剩余rest步，当前在cur
        if (rest==0) {      //没路了
            return cur == P ? 1 : 0;
        }
        //rest > 0
        if (cur==1) {       //只能走到2位置
            return process1_Recursion(N, P, rest-1, 2);
        }
        if (cur==N) {       //只能走到2位置
            return process1_Recursion(N, P, rest-1, N-1);
        }
        return process1_Recursion(N, P, rest-1, cur-1) + process1_Recursion(N, P, rest-1, cur+1);
    }
/*****************************************************************************************************************/
    int walk_cache(int N, int M, int K, int P) {    // 总共N个格子，目标P，走K步，初始位于M
        vector<vector<int>> dp (K+1, vector<int>(N+1, -1));     // 记录每个子问题的值
        return process1_cache(N, P, K, M, dp);
    }

    int process1_cache(int N, int P, int rest, int cur, vector<vector<int>> dp) {    // 总共N个格子，目标P，剩余rest步，当前在cur
        if (dp[rest][cur] != -1) {      //直接返回子问题解
            return dp[rest][cur]; 
        }
        //增加记录
        if (rest==0) {      //没路了
            return cur == P ? 1 : 0;
        }
        //rest > 0
        int res = 0;
        if (cur==1) {       //只能走到2位置
            res = process1_cache(N, P, rest-1, 2, dp);
        }
        else if (cur==N) {       //只能走到2位置
            res = process1_cache(N, P, rest-1, N-1, dp);
        }
        else {
            res = process1_cache(N, P, rest-1, cur-1, dp) + process1_cache(N, P, rest-1, cur+1, dp);
        }
        dp[rest][cur] = res;
        return res;
    }
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
    int walk_DP(int N, int M, int K, int P) {    // 总共N个格子，目标P，走K步，初始位于M
        vector<vector<int>> dp (N+1, vector<int>(K+1, 1));     // 记录每个子问题的值
        // rest循环 列循环
        for (int j = 1; j <= N; j++) {
            dp[1][j] = dp[2][j-1];
            // cur循环 行循环
            for (int i = 2; i < N; i++) {
                dp[i][j] = dp[i-1][j-1] + dp[i+1][j-1];
            }
            dp[N][j] = dp[N-1][j-1];
        }
        return dp[M][K];
    }
};

int main() {
    robot_walk rw;
    clock_t start,end; start=clock();
    // N M K P
    int res = rw.walk_Recursion(5, 5, 5, 4);
    end=clock();

    cout << "Recursion" << " | " << res << " | " << "run time:" << ' ' << (double)(end-start)*1000/CLOCKS_PER_SEC << "ms" << endl;


    start=clock();
    // N M K P
    res = rw.walk_cache(5, 5, 5, 4);
    end=clock();

    cout << "cache" << " | " << res << " | " << "run time:" << ' ' << (double)(end-start)*1000/CLOCKS_PER_SEC << "ms" << endl;

    start=clock();
    // N M K P
    res = rw.walk_DP(5, 5, 5, 4);
    end=clock();

    cout << "DP" << " | " << res << " | " << "run time:" << ' ' << (double)(end-start)*1000/CLOCKS_PER_SEC << "ms" << endl;
    
    return 0;
}
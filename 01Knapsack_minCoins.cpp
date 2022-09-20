#include<bits/stdc++.h>
using namespace std;

class Solution{
public:
    int select_Recursion(vector<int> knapsack, int aim) {
        return Recursion(knapsack, 0, aim);
    }
    //递归
    //固定参数 knapsack 和 目标 aim
    // index 当前可选的位置
    // rest 当前选择时剩余的值
    int Recursion(vector<int> knapsack, int index, int rest) {
        if (rest == 0) {
            return 0;
        }
        if (rest < 0) {
            return -1;
        }
        if (index == knapsack.size()) {
            return -1;
        }
        //当前位置 不拿 和 拿 两种情况
        int p1 = Recursion(knapsack, index+1, rest);
        int p2Next = Recursion(knapsack, index+1, rest-knapsack[index]);
        if (p1 == -1 && p2Next == -1) {
            return -1;
        } else if (p1 == -1) {
            return p2Next + 1;
        } else if (p2Next == -1) {
            return p1;
        } else {
            return min(p1, p2Next+1);
        }
    }
/************************************************************************************************/
    int select_Cache(vector<int> knapsack, int aim) {
        vector<vector<int>> cache (knapsack.size()+1, vector<int> (aim+1, -2));
        return Cache(knapsack, 0, aim, cache);
    }
    //递归
    //固定参数 knapsack 和 目标 aim
    // index 当前可选的位置
    // rest 当前选择时剩余的值
    int Cache(vector<int> knapsack, int index, int rest, vector<vector<int>> cache) {
        if (rest < 0) {
            return -1;
        }
        //缓存命中
        if (cache[index][rest] != -2) {
            return cache[index][rest];
        }
        //未命中
        if (rest == 0) {
            cache[index][rest] = 0;
        } else if (index == knapsack.size()) {
            cache[index][rest] = -1;
        } else {
            //当前位置 不拿 和 拿 两种情况
            int p1 = Cache(knapsack, index+1, rest, cache);
            int p2Next = Cache(knapsack, index+1, rest-knapsack[index], cache);
            if (p1 == -1 && p2Next == -1) {
                cache[index][rest] = -1;
            } else if (p1 == -1) {
                cache[index][rest] = p2Next + 1;
            } else if (p2Next == -1) {
                cache[index][rest] = p1;
            } else {
                cache[index][rest] = min(p1, p2Next+1);
            }
        }
        return cache[index][rest];
    }
/************************************************************************************************/
    int select_dp_table(vector<int> knapsack, int aim) {
        //index 种的行；aim数的列
        int len = knapsack.size();
        vector<vector<int>> cache (len+1, vector<int> (aim+1, -2));
        for (int row = 0; row <= len; row++) {
            cache[row][0] = 0;
        }
        for (int col = 1; col <= aim; col++) {
            cache[len][col] = -1;
        }
        //状态依赖 从下往上，从左往右
        for (int index = len-1; index >= 0; index--) {
            for (int rest = 1; rest <= aim; rest++) {
                //当前位置 不拿 和 拿 两种情况
                int p1 = cache[index+1][rest];
                int p2Next = -1;
                if (rest-knapsack[index] >= 0) {
                    p2Next = cache[index+1][rest-knapsack[index]];
                }
                if (p1 == -1 && p2Next == -1) {
                    cache[index][rest] = -1;
                } else if (p1 == -1) {
                    cache[index][rest] = p2Next + 1;
                } else if (p2Next == -1) {
                    cache[index][rest] = p1;
                } else {
                    cache[index][rest] = min(p1, p2Next+1);
                }
            }
        }
        return cache[0][aim];
    }

};

void printtime(string type, int time) {
    cout << type << "run time:" << ' ' << time << "ms" << endl;
    return;
}


int main() {
    srand(42);
    vector<int> knapsack (10);
    int aim = 25;
    Solution s;
    int res1 = 0;
    int res2 = 0;
    int res3 = 0;
    double rt1, rt2, rt3;
    vector<int> res_1, res_2, res_3;
    clock_t start,end; 
    
    int testtime = 500;
    for (int i=0; i<testtime; i++) {
        generate (knapsack.begin(), knapsack.end(), []() 
        {
            return rand() % 10;
        }
        );

        start=clock();
        res1 = s.select_Recursion(knapsack, aim);
        end=clock();
        rt1 += (double)(end-start)*1000/CLOCKS_PER_SEC;
        res_1.push_back(res1);

        start=clock();
        res2 = s.select_Cache(knapsack, aim);
        end=clock();
        rt2 += (double)(end-start)*1000/CLOCKS_PER_SEC;
        res_2.push_back(res2);

        start=clock();
        res3 = s.select_dp_table(knapsack, aim);
        end=clock();
        rt3 += (double)(end-start)*1000/CLOCKS_PER_SEC;
        res_3.push_back(res3);
    }
    for (int i=0; i<testtime; i++) {
        if (res_1[i]==res_2[i] && res_2[i]==res_3[i]) {
            continue;
        } else {
            cout << "False" << endl;
            break;
        }
    }
    printtime("Recursion", rt1);
    printtime("Cache", rt2);
    printtime("DP Table", rt3);
    return 0;
}
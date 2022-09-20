#include<bits/stdc++.h>

using namespace std;
class Solution {
public:
    vector<vector<string>> results;
    vector<vector<string>> solveNQueens(int n) {
        // vector<vector<string>> results;
        vector<int> cols;
        search(results, cols, n);
        for (const auto& x : results){
            for (const auto& j : x) {
                cout << j << ' ';
            }
            cout << endl;
        }
        return results;
    }

    void search(vector<vector<string>>& results, vector<int> cols, int n) {
        if (cols.size() == n) {
            results.push_back(Draw(cols));
            // for (const auto& x : results){
            //     for (const auto& j : x) {
            //         cout << j << ' ';
            //     }
            //     cout << endl;
            // }
            return;
        }
        // 枚举当前皇后放置的列，若不合法则跳过
        for (int colIndex = 0; colIndex < n; colIndex++) {
            if (!isValid(cols, colIndex)) {
                continue;
            }
            // 若合法则递归枚举下一行的皇后
            cols.push_back(colIndex);
            search(results, cols, n);
            cols.pop_back();
        }
    }

    // Draw函数为将 cols 数组转换为答案的绘制函数
    vector<string> Draw(vector<int> cols) {
        vector<string> result;
        for (int i = 0; i < cols.size(); i++) {
            string sb;
            for (int j = 0; j < cols.size(); j++) {
                sb.push_back(j == cols[i] ? 'Q' : '.');
            }
            // cout << sb << endl;
            result.push_back(sb);
            // for (const auto& x : result) {
            //     cout << x << endl;
            // }
        }
        return result;
    }

    // isValid函数为合法性判断函数
    bool isValid(vector<int> cols, int col) {
        int row = cols.size();
        for (int rowIndex = 0; rowIndex < cols.size(); rowIndex++) {
            //若有其他皇后在同一列或同一斜线上则不合法
            if (cols[rowIndex] == col) {
                return false;
            }
            if (row + col == rowIndex + cols[rowIndex]) {
                return false;
            }
            if (row - col == rowIndex - cols[rowIndex]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    int n;
    cin >> n;
    vector<vector<string>> results;
    results = s.solveNQueens(n);
    // for (const auto& x : results){
    //     for (const auto& j : x) {
    //         cout << j << ' ';
    //     }
    //     cout << endl;
    // }

    return 0;
}

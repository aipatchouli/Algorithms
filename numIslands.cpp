#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    char a = '0';
    char b = '1';
    char c = '2';
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    res += 1;
                    infect(grid, i, j, m, n);
                }
            }
        }
        return res;
    }

    void infect(vector<vector<char>>& grid, int i, int j, int m, int n) {
        if (i >= m || i<0 || j >= n || j <0 || grid[i][j] != '1') {
            return;
        }
        grid[i][j] = '2';
        infect(grid, i+1, j, m, n);
        infect(grid, i-1, j, m, n);
        infect(grid, i, j+1, m, n);
        infect(grid, i, j-1, m, n);
    }
};

int main() {
    // int m = 5;
    // int n = 5;
    // vector<vector<char>> grid (m, vector<char>(n, '0'));
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         grid[i][j] = '1';
    //     }
    // }

    // for (int i = 0; i < 5; i++) {
    //     for (int j = 0; j < 5; j++) {
    //         cout << grid[i][j];
    //     }
    //     cout << endl;
    // }

    char a = '1';
    char b = '2';
    cout << (a != b ? 1 : 2) << endl;
    return 0;
}
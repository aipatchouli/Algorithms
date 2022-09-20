#include<bits/stdc++.h>
using namespace std;

/* class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    res = max(res, dfs(grid, i, j));
                }
            }
        }
        return res;
    }

    int dfs(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == 0) {
            return 0;
        }
        grid[i][j] = 0;
        return 1 + dfs(grid, i+1, j) + dfs(grid, i-1, j) + dfs(grid, i, j+1) + dfs(grid, i, j-1);
    }
}; */


class Solution {
private:
    int findSet(vector<int>& parent, int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = findSet(parent, parent[x]);
    }

    void unionSet(vector<int>& parent, vector<int>& rank, int x, int y) {
        int px = findSet(parent, x);
        int py = findSet(parent, y);
        if (px == py) {return;}
        if (rank[px] > rank[py]) {
            parent[py] = px;
            rank[px] += rank[py];
        } else {
            parent[px] = py;
            rank[py] += rank[px];
        }
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> parent(m*n, 0);
        vector<int> rank(m*n, 0);
        for (int i = 0; i < m*n; ++i) {
            parent[i] = i;
        }
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    int cur = i*n + j;
                    rank[cur] = 1;
                    if (i > 0 && grid[i-1][j] == 1) {
                        int up = (i-1)*n + j;
                        unionSet(parent, rank, cur, up);
                    }
                    if (j > 0 && grid[i][j-1] == 1) {
                        int left = i*n + j - 1;
                        unionSet(parent, rank, cur, left);
                    }
                }
            }
        }
        return *max_element(rank.begin(), rank.end());
    }
};


/* class Solution { // 最大人工岛
public:
    int largestIsland(vector<vector<int>>& grid) {
        
        // for (int i = 0; i < m; ++i) {
        //     for (int j = 0; j < n; ++j) {
        //         if (grid[i][j] == 0) {
        //             int cur = i*n + j;
        //             int up = (i-1)*n + j;
        //             int left = i*n + j - 1;
        //             int upSet = i > 0 ? findSet(parent, up) : -1;
        //             int leftSet = j > 0 ? findSet(parent, left) : -1;
        //             int upRank = upSet != -1 ? rank[upSet] : 0;
        //             int leftRank = leftSet != -1 ? rank[leftSet] : 0;
        //             res = max(res, upRank + leftRank + 1);
        //         }
        //     }
        // }
        
    }
}; */

int main() {
    vector<vector<int>> grid = {{1, 0}, {0, 1}};
    Solution s;
    cout << s.largestIsland(grid) << endl;
    return 0;
}
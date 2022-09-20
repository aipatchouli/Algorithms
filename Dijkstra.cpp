// 朴素版 朴素Dijkstra算法的时间复杂度是 O(n^2)，适合稠密图（点少边多）（邻接矩阵）
// 核心：一遍一遍地扫点
#include<bits/stdc++.h>
using namespace std;

const int N = 510;

// g存邻接矩阵，dist[j]存从1到j的距离
int g[N][N], dist[N];
// st[j]为true时表示j在S数组里，即已经确定距离
bool st[N];

// 计算结点1到结点n的最短距离
int dijkstra(int n) {
    // dist数组也初始化为正无穷，表示没计算过
    memset(dist, 0x3f, sizeof dist);
    // 到1自己的距离为0
    dist[1] = 0;
    // 只要循环n-1次，因为每次都会在S外找一个dist最小的
    // n-1次之后，S里已经有n-1个元素，如果有第n轮一定直接选到最后那个元素了
    // 所以没必要做到n轮，n-1轮之后dist就已经算完了
    for (int i = 0; i < n - 1; i ++ ) {
        // 在S外（st[j]为false的）找一个最小的dist[t]
        int t = -1;
        for (int j = 1; j <= n; j ++ ) {
            if (!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        }
        // 将其加入到S中
        st[t] = true;
        // 用它来更新到其它点的距离，这里不需要判断只更新没确定的
        // 因为即使是已经确定的，这样求min的更新也不会破坏它
        for (int j = 1; j <= n; j ++ )
            dist[j] = min(dist[j], dist[t] + g[t][j]); // 核心：先确定近的，再推进到远的
    }
    // 如果要求的n号点还是正无穷，那说明不可达
    if (dist[n] == 0x3f3f3f3f) return -1;
    // 否则dist[n]就是1号点到n号点的距离
    return dist[n];
}

int main() {
    // 图里每条边都初始化为正无穷，表示不可达
    memset(g, 0x3f, sizeof g);
    int n, m;
    cin >> n >> m;
    while (m -- ) {
        int x, y, z;
        cin >> x >> y >> z;
        // 由于有重边，两个结点之间只要记录最短的
        // 所以这里取min
        g[x][y] = min(g[x][y], z);
    }
    // 输出从结点1到结点n的最短距离
    cout << dijkstra(n) << endl;
    return 0;
}
// 堆优化 Dijkstra算法的时间复杂度是 O(mlogn)，m为边数，n为点数,适合稀疏图（点少边多）（邻接表）
// 核心：遍历 边
#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

const int N = 150010, M = N;

// 带权w的邻接表
int h[N], e[M], ne[M], idx, w[M];
void add_edge(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a]; // next
    h[a] = idx ++ ;
}

int dist[N];
bool st[N];

int dijkstra(int n) {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    // 存pair<int, int>的小根堆
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    // 到1距离为0
    heap.push({0, 1});
    
    // 这里不用n-1次这样遍历了，直接遍历到堆空
    while (heap.size()) {
        // 取出堆顶，就是最小的距离
        // 注意这里不能用auto&，因为pop之后这个top()就变了
        auto t = heap.top();
        heap.pop();
        // 但是这个距离可能已经是算过的S里的点的了
        int ver = t.second, distance = t.first;
        if (st[ver]) 
            continue;
        // 至此，说明是S外的点，把它加到S里
        st[ver] = true;
        // 遍历ver连接的所有边，更新t连接的结点j的dist
        for (int i = h[ver]; i != -1; i = ne[i]) {
            // 这条边的结点号是j
            int j = e[i];
            // 更新
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                // 如果更新了，还要把它加入到堆里
                // 本来应该修改，但是用STL的修改不了，直接加
                heap.push({dist[j], j});
            }
        }
    }
    // 最后一样的判断n号点距离
    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main() {
    // 清空邻接表
    memset(h, -1, sizeof h);
    int n, m;
    cin >> n >> m;
    while (m -- ) {
        int x, y, z;
        cin >> x >> y >> z;
        // 直接在邻接表里加边
        add_edge(x, y, z);
    }
    cout << dijkstra(n) << endl;
    return 0;
}

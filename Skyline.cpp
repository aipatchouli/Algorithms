#include<bits/stdc++.h>
using namespace std;

class SolutionScanLine {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) -> bool { return a.second < b.second; };
        priority_queue <pair<int, int>, vector<pair<int, int>>, decltype(cmp)> que(cmp); //大根堆

        vector<int> boundaries; //扫描 有意义的位置
        for (auto& building : buildings) {
            boundaries.emplace_back(building[0]);//开始
            boundaries.emplace_back(building[1]);//结束
        }
        sort(boundaries.begin(), boundaries.end()); //排序 

        vector<vector<int>> ret;
        int n = buildings.size(), idx = 0;
        for (auto& boundary : boundaries) { 
            while (idx < n && buildings[idx][0] <= boundary) { //boundary 表示当前记录到的边界
                que.emplace(buildings[idx][1], buildings[idx][2]);//记录终止位置 和 高度
                idx++;
            }
            while (!que.empty() && que.top().first <= boundary) { // first 是终止位置 
                que.pop(); // 意思是 在边界 前的 房子 应当出界 无用了
            }

            int maxn = que.empty() ? 0 : que.top().second; // 记录当前扫描到的最大高度
            if (ret.size() == 0 || maxn != ret.back()[1]) { // 将高度变化记录
                ret.push_back({boundary, maxn});
            }
        }
        return ret;
    }
};


class SolutionMultiSet {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> res;
        vector<pair<int, int>> height;
        for (auto &b : buildings) {
            // 正负用于判别是左端点还是右端点，同时保证排序后：
            // 左端点相同时，最高的楼排在前面，insert的一定是相同左端点中最大的高度
            // 右端点相同时，最低的楼排在前面，erase的时候不会改变最大高度
            height.push_back({b[0], -b[2]}); // 左端点
            height.push_back({b[1], b[2]});  // 右端点
        }
        sort(height.begin(), height.end());
        // 维护当前最大高度
        multiset<int> st;
        st.insert(0); // 保证端点全部删除之后能得到当前最大高度为 0
        // preMaxHeight 表示遇到一个端点之前的最大高度
        // curMaxHeight 表示遇到一个端点之后的当前最大高度
        int preMaxHeight = 0, curMaxHeight = 0;
        for (auto &h : height) {
            if (h.second < 0) { // 左端点
                st.insert(-h.second);
            } else { // 右端点
                st.erase(st.find(h.second));
            }
            
            curMaxHeight = *st.rbegin();
            // 最大高度发生改变，一定是一个 key point，即一个水平线段的左端点
            if (curMaxHeight != preMaxHeight) {
                res.push_back({h.first, curMaxHeight});
                preMaxHeight = curMaxHeight;
            }
        }
        return res;
    }
};

struct SegTree{
    int left,right;
    SegTree *lchild,*rchild;
    int height;
    int lazy;
    SegTree(int l,int r):left(l),right(r),lchild(nullptr),rchild(nullptr),height(0),lazy(0) {};
};
class SolutionSegTree {
public:
    void pushdown(SegTree* root){
        if(root->left==root->right){
            root->height = root->lazy;
            root->lazy = 0;
            return;
        }
        if(root->lchild){
            root->lchild->lazy = max(root->lchild->lazy,root->lazy);
        }
        if(root->rchild){
            root->rchild->lazy = max(root->rchild->lazy,root->lazy);
        }
        root->lazy = 0;
    }
    void update(vector<int>& building,SegTree* root){
        int l = building[0], r = building[1], height = building[2];
        if(root->left>=l && root->right<=r){
            root->lazy = max(root->lazy,height);
            return;
        }
        long long mid = ((long long)(root->left)+(long long)(root->right))/2;
        if(r<=mid){
            if(root->lchild) update(building,root->lchild);
        }else if(l>mid){
            if(root->rchild) update(building,root->rchild);
        }else{
            if(root->lchild) update(building,root->lchild);
            if(root->rchild) update(building,root->rchild);
        }        
    }
    void insert(int b,SegTree* root){
        
        long long mid = ((long long)(root->left)+(long long)(root->right))/2;
        if(root->left == root->right){
            return;
        }else if(b<=mid){
            if(!root->lchild) root->lchild = new SegTree(root->left,mid);
            insert(b,root->lchild);
        }else{
            if(!root->rchild) root->rchild = new SegTree(mid+1,root->right);
            insert(b,root->rchild);
        }
    }
    void query(vector<vector<int>>& res,SegTree* root){
        if(root->lazy){
            pushdown(root);
        }
        if(root->lchild){
            query(res,root->lchild);
        }
        if(root->rchild){
            query(res,root->rchild);
        }
        if(root->left==root->right){
            if(res.size()==0 || res.back()[1] != root->height) //相邻的同一高度的边界点只取最前面的
                res.push_back({root->left,root->height}); 
            return;
        }
    }
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        //获取所有的边界点并去重
        set<int> boundary;
        for(auto building : buildings){
            boundary.insert(building[0]);
            boundary.insert(building[1]);
        }
        //获取最小边界与最大边界初始化线段树根节点
        int minval = *boundary.begin();
        int maxval = *boundary.rbegin();
        SegTree* root = new SegTree(minval,maxval);
        //插入边界点
        for(auto b : boundary){
            insert(b,root);
        }
        //区间更新
        for(auto building : buildings){
            --building[1];
            update(building,root);
        }
        //单点查询所有叶子节点，一个叶子节点表示一个边界点
        vector<vector<int>> res;
        query(res,root);
        return res;
    }
};


int main() {
    vector<vector<int>> buildings {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    SolutionScanLine s;
    vector<vector<int>> res = s.getSkyline(buildings);
    for (const auto& x : res) {
        for (const auto& y : x) {
            cout << y << ',';
        }
        cout << endl;
    }
    return 0;
}
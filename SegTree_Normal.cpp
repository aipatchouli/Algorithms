#include<bits/stdc++.h>
using namespace std;

/* 
简单求区间和，用「前缀和」
多次将某个区间变成同一个数，用「线段树」
其他情况，用「树状数组」
*/

// segtree 线段树 （区间修改树）O(log n)
struct SegTree{
    int left,right;
    SegTree *lchild,*rchild;
    int height;
    int lazy;
    SegTree(int l,int r):left(l),right(r),lchild(nullptr),rchild(nullptr),height(0),lazy(0) {};
};

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
void update(vector<int>& building, SegTree* root){
    int l = building[0], r = building[1], height = building[2];
    if(root->left>=l && root->right<=r){
        root->lazy = max(root->lazy, height);
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
/**************************************//**********************************************************/
/**************************************//**********************************************************/

// ZKW线段数
// 假设要维护的信息有：区间和，区间最小值，区间最大值

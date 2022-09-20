#include<bits/stdc++.h>
using namespace std;

template <typename T>
class SegTreeRangeAdd {
private:
    vector<T> tree, lazy;
    vector<T> arr;
    int n, root, n4, end;

    void maintain(int cl, int cr, int p) {
        int cm = (cl + cr) >> 1;
        if (cl != cr && lazy[p] != 0) {
            lazy[p << 1] += lazy[p];
            lazy[p << 1 | 1] += lazy[p];
            tree[p << 1] += (cm - cl + 1) * lazy[p];
            tree[p << 1 | 1] += (cr - cm) * lazy[p];
            lazy[p] = 0;
        }
    } // 更新 lazy

    T range_sum(int l, int r, int cl, int cr, int p) {
        if (l <= cl && cr <= r) { // 当前节点范围被覆盖
            return tree[p]; 
        } else {
            maintain(cl, cr, p);
            int cm = (cl + cr) >> 1;
            T sum = 0;
            if (l <= cm) {
                sum += range_sum(l, r, cl, cm, p << 1);
            }
            if (r > cm) {
                sum += range_sum(l, r, cm + 1, cr, p << 1 | 1);
            }
            return sum;
        }
    } // 区间求和

    void range_add(int l, int r, int cl, int cr, int p, T val) {
        if (l <= cl && cr <= r) { // 当前节点范围被覆盖
            tree[p] += (cr - cl + 1) * val;
            lazy[p] += val;
            return;
        } else {
            maintain(cl, cr, p);
            int cm = (cl + cr) >> 1;
            if (l <= cm) {
                range_add(l, r, cl, cm, p << 1, val);
            }
            if (r > cm) {
                range_add(l, r, cm + 1, cr, p << 1 | 1, val);
            }
            tree[p] = tree[p << 1] + tree[p << 1 | 1];
        }
    } // 区间内 都加

    void build(int s, int t, int p) {
        if (s == t) {
            tree[p] = arr[s];
            return;
        } else {
            int m = (s + t) >> 1;
            build(s, m, p << 1);
            build(m + 1, t, p << 1 | 1);
            tree[p] = tree[p << 1] + tree[p << 1 | 1];
        }
    } // 构建线段树
    
public:
    explicit SegTreeRangeAdd <T> (vector<T>& v) { // 返回类型 类名 <类型参数> 函数名（形参）
        n = v.size();
        n4 = n << 2;
        root = 1;
        end = n - 1;
        arr = v;
        tree = vector<T>(n4, 0);
        lazy = vector<T>(n4, 0);
        build(0, end, root);
        vector<T>().swap(arr); //释放arr
    }

    T range_sum(int l, int r) {
        return range_sum(l, r, 0, end, root);
    }

    void range_add(int l, int r, T val) {
        range_add(l, r, 0, end, root, val);
    }
};

/**************************************************************************************/

template <typename T>
class SegTreeRangeSet {
private:
    vector<T> tree, lazy;
    vector<T> arr;
    int n, root, n4, end;

    void maintain(int cl, int cr, int p) {
        int cm = (cl + cr) >> 1;
        if (cl != cr && lazy[p] != 0) {
            lazy[p << 1] = lazy[p];
            lazy[p << 1 | 1] = lazy[p];
            tree[p << 1] = (cm - cl + 1) * lazy[p];
            tree[p << 1 | 1] = (cr - cm) * lazy[p];
            lazy[p] = 0;
        }
    } // 更新 lazy

    T range_sum(int l, int r, int cl, int cr, int p) {
        if (l <= cl && cr <= r) { // 当前节点范围被覆盖
            return tree[p]; 
        } else {
            maintain(cl, cr, p);
            int cm = (cl + cr) >> 1;
            T sum = 0;
            if (l <= cm) {
                sum += range_sum(l, r, cl, cm, p << 1);
            }
            if (r > cm) {
                sum += range_sum(l, r, cm + 1, cr, p << 1 | 1);
            }
            return sum;
        }
    } // 区间求和

    void range_set(int l, int r, int cl, int cr, int p, T val) {
        if (l <= cl && cr <= r) { // 当前节点范围被覆盖
            tree[p] = (cr - cl + 1) * val;
            lazy[p] = val;
            return;
        } else {
            maintain(cl, cr, p);
            int cm = (cl + cr) >> 1;
            if (l <= cm) {
                range_set(l, r, cl, cm, p << 1, val);
            }
            if (r > cm) {
                range_set(l, r, cm + 1, cr, p << 1 | 1, val);
            }
            tree[p] = tree[p << 1] + tree[p << 1 | 1];
        }
    } // 区间内 都加

    void build(int s, int t, int p) {
        if (s == t) {
            tree[p] = arr[s];
            return;
        } else {
            int m = (s + t) >> 1;
            build(s, m, p << 1);
            build(m + 1, t, p << 1 | 1);
            tree[p] = tree[p << 1] + tree[p << 1 | 1];
        }
    } // 构建线段树
    
public:
    explicit SegTreeRangeSet <T> (vector<T>& v) { // 返回类型 类名 <类型参数> 函数名（形参）
        n = v.size();
        n4 = n << 2;
        root = 1;
        end = n - 1;
        arr = v;
        tree = vector<T>(n4, 0);
        lazy = vector<T>(n4, 0);
        build(0, end, root);
        vector<T>().swap(arr); //释放arr
    }

    T range_sum(int l, int r) {
        return range_sum(l, r, 0, end, root);
    }

    void range_set(int l, int r, T val) {
        range_set(l, r, 0, end, root, val);
    }
};

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
class segtree {
public:
    int n;
    vector<int> tree, lazy;
    segtree(int n) {
        this->n = n;
        this->tree = vector<int>(n * 4, 0); // 实际可 定义复杂 struct 
        // this->lazy = vector<int>(n * 4, 0);
    }

private:
    void Update(int x) { // 更新第 x 个位置的值
        tree[x] = tree[x << 1] + tree[x << 1 | 1];
    }

    void Build(int x, int l, int r, vector<int> &arr) { // 构建线段树
        if (l < r) {
            int mid = (l + r) >> 1;
            Build(x << 1, l, mid, arr);
            Build(x << 1 | 1, mid + 1, r, arr);
            Update(x);
        } else {
            tree[x] = arr[l];
        }
    }

    void Modify(int cur, int l, int r, int q, int val) { // 当前处于cur,l r为cur的范围,修改第q个位置的值
        if (l == r) {
            tree[cur] = val;
            return;
        } else {
            int mid = (l + r) >> 1;
            if (q <= mid) {
                Modify(cur << 1, l, mid, q, val);
            } else {
                Modify(cur << 1 | 1, mid + 1, r, q, val);
            }
            Update(cur);
        }
    }

    // void PushTag(int x, int l, int r) { // 更新第 x 个位置的值
    //     lazy[x << 1] += lazy[x];
    //     lazy[x << 1 | 1] += lazy[x];
    //     int mid = (l + r) >> 1;
    //     if (lazy[x] != 0) {
    //         tree[x << 1] += (mid - l + 1) * lazy[x];
    //         tree[x << 1 | 1] += (r - mid) * lazy[x];
    //     }
    //     lazy[x] = 0;
    // } 

    int Query(int cur, int l, int r, int ql, int qr) { // 当前处于cur,l r为cur的范围,查询[ql,qr]的值
        if (ql <= l && r <= qr) {
            return tree[cur]; // 如果这个节点表示区间被 [ql, qr] 包含, 就返回这个节点的值
        } else {
            int mid = (l + r) >> 1;
            int left = Query(cur << 1, l, mid, ql, qr);
            int right = Query(cur << 1 | 1, mid + 1, r, ql, qr);
            return left + right;
        }
    }
};


class RangeModule {
public:
    struct node{
        node() {ls = rs = val = lazy = 0;}
        int ls, rs , val , lazy;
    } tr[500010];
    int N = (int)1e9 + 10;
    int cnt = 1;


    void pushUp(int u) {
        tr[u].val = tr[tr[u].ls].val + tr[tr[u].rs].val;
    }
    void pushDown(int u, int l ,int r) {
        int len = r - l + 1;
        if (tr[u].ls == 0) {
            tr[u].ls = ++cnt;
        }
        if (tr[u].rs == 0) {
            tr[u].rs = ++cnt;
        }
        if (tr[u].lazy == 0) return;
        if (tr[u].lazy == -1) {
            tr[tr[u].ls].val = tr[tr[u].rs].val = 0;
        } else {
            tr[tr[u].ls].val = len - len / 2;
            tr[tr[u].rs].val = len / 2;
        }
        tr[tr[u].ls].lazy = tr[tr[u].rs].lazy = tr[u].lazy;
        tr[u].lazy = 0;
    }

    void updata(int u, int l, int r, int start, int end , int delta) {
        if(l > end || r < start){
            return;
        }else if(start <= l && r <= end){
            tr[u].val = delta == 1 ? (r - l + 1) : 0 ;
            tr[u].lazy = delta;
            return ;
        }else{
            int m = (l + r) >> 1;
            pushDown(u, l , r); // 更新下一层节点的值
            if (start <= m) {
                updata(tr[u].ls, l, m, start, end, delta);
            }
            if (end > m) {
                updata(tr[u].rs, m + 1, r, start, end, delta);
            }
            //根据子节点更新自己的值
            pushUp(u);
  
        }
    }

    int query(int u, int l, int r, int start, int end ) {
        if(l > end || r < start){
            return 0;
        }else if(start <= l && r <= end){
            return tr[u].val;
        }else{
            pushDown(u, l , r); // 更新下一层节点的值

            int m = (l + r) >> 1;
            int res = 0;
            if(start <= m){
                res =  query(tr[u].ls, l , m , start, end);
            }
            if(end > m){
                res += query(tr[u].rs, m + 1, r, start ,end);
            }
            return res;
        }
    }
};
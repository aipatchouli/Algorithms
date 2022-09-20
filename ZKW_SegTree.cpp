#include<bits/stdc++.h>
using namespace std;

/*
ZKW :   1. 强制连续存储：ZKW线段树强制存在连续的内存空间中(数组，vector等)，从而带来较好的局部性
        2. 满二叉树型存储：通过类似二叉堆的索引方式存储整颗线段树，从而避免存储额外的左右子树指针/父节点指针等，从而节约内存空间
        3. 递推+位运算操作：任何操作都只需要一个while+若干位运算，常数极低

A. 区间必须严格遵从 [1,n] (n>=1)的格式 *** 注意是 从 1 开始, 到 n 结束 ***
B. n = 2^x − 2, x∈Z
C. 将 [1,n] 补齐为 [0, n+1], 使得总叶节点数量为 n+2 == 2^x , 且 叶节点 位于 满二叉树第 x+1 层
*/

//定义常数
#define MAXN 100005
int num = 1; // 给定 size() + 2
int sigma = 1; //偏移量 满足 n+2 == 2^x 最小的 n
// while(sigma < num) {
//     sigma <<= 1;
// }
vector<int> zkwTree (MAXN<<2, 0); // 开一个足够大的数组 4倍足够

// 单点更新
void update(const vector<int>& zkwTree, int position, int value) { // 更新第 position 个位置的值
    position += sigma; // 从 标准数组下标 得到 zkwtree 下标
    while (position > 0) {
        zkwTree[position] = max(zkwTree[position], value);
        position >>= 1;
    }
}
// 区间查询
int query(const vector<int>& zkwTree, int start, int end) { // 左边界 start, 右边界 end 均为闭区间
    start += sigma - 1; // 左减 右加 得到开区间
    end += sigma + 1;
    auto answer = 0;
    while (start < end-1) {
        if (start & 1 == 0) // 偶数位 说明本身处于左子树 
            answer = max(answer, zkwTree[start ^ 1]); // 有效信息在右边 
        if (end & 1 == 1) // 奇数位 说明本身处于右子树
            answer = max(answer, zkwTree[end ^ 1]); // 有效信息在左边
        start >>= 1;
        end >>= 1;
    }
    return answer;
}
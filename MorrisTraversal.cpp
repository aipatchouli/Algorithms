#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptrptr), right(nullptrptr) {}
    TreeNode(int x) : val(x), left(nullptrptr), right(nullptrptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// morris遍历利用的是树的叶节点左右孩子为空（树的大量空闲指针），实现空间开销的极限缩减，空间复杂度降为O(1)
// 对于没有左子树的节点只到达一次，对于有左子树的节点会到达两次
/*_________________________________________________________________________________________________________
    如果cur无左孩子，cur向右移动（cur=cur.right）
    如果cur有左孩子，找到cur左子树上最右的节点，记为mostright
        如果mostright的right指针指向空，让其指向cur，cur向左移动（cur=cur.left）
        如果mostright的right指针指向cur，让其指向空，cur向右移动（cur=cur.right）
*/
// 先序遍历 preorder
void preorderMorrisTraversal(TreeNode *root) {
    TreeNode *cur = root, *mostRight = nullptr; //cur表示当前节点，mostRight表示cur的左孩子的最右节点
    while (cur != nullptr) {
        if (cur->left == nullptr) {
            // printf("%d ", cur->val); 操作
            cur = cur->right; // 无左 只遇到一次 向右移动
        }
        else {
            mostRight = cur->left; //左子树上的
            while (mostRight->right != nullptr && mostRight->right != cur) { //最右节点
                mostRight = mostRight->right;
            }
            if (mostRight->right == nullptr) {
                // printf("%d ", cur->val);  第一次见，操作
                mostRight->right = cur; // 记录 cur ,方便回去
                cur = cur->left;
            }
            else { // 回头 向右走
                mostRight->right = nullptr;
                cur = cur->right;
            }
        }
    }
}

// 中序遍历 inorder
void inorderMorrisTraversal(TreeNode *root) {
    TreeNode *cur = root, *mostRight = nullptr;
    while (cur != nullptr) {
        if (cur->left == nullptr) {
            // printf("%d ", cur->val);
            cur = cur->right;
        }
        else {
            // find predecessor
            mostRight = cur->left;
            while (mostRight->right != nullptr && mostRight->right != cur)
                mostRight = mostRight->right;

            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cur = cur->left;
            }
            else {
                mostRight->right = nullptr;
                // printf("%d ", cur->val); 第二次见，操作 |||||| 先序中序的唯一区别
                cur = cur->right;
            }
        }
    }
}

// 后序遍历 postorder
void reverse(TreeNode *from, TreeNode *to) { // reverse the tree nodes 'from' -> 'to'.
    if (from == to)
        return;
    TreeNode *x = from, *y = from->right, *z;
    while (true) {
        z = y->right;
        y->right = x;
        x = y;
        y = z;
        if (x == to)
            break;
    }
}

void printReverse(TreeNode* from, TreeNode *to) { // print the reversed tree nodes 'from' -> 'to'.
    reverse(from, to);
    TreeNode *p = to;
    while (true) {
        printf("%d ", p->val);
        if (p == from)
            break;
        p = p->right;
    }
    reverse(to, from);
}

void postorderMorrisTraversal(TreeNode *root) {
    TreeNode dump(0);
    dump.left = root;
    TreeNode *cur = &dump, *mostRight = nullptr;
    while (cur) {
        if (cur->left == nullptr) {
            cur = cur->right;
        }
        else {
            mostRight = cur->left;
            while (mostRight->right != nullptr && mostRight->right != cur)
                mostRight = mostRight->right;

            if (mostRight->right == nullptr) {
                mostRight->right = cur;
                cur = cur->left;
            }
            else { // 类似与 中序（左 中 右），但是需要将 中 右 输出顺序交换得到（左 右 中）
                printReverse(cur->left, mostRight);  // call print
                mostRight->right = nullptr;
                cur = cur->right;
            }
        }
    }
}
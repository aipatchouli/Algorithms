#include <iostream>
using namespace std;

class BSTNode {
	private:
		double key;
		BSTNode *lchild;
		BSTNode *rchild;
		BSTNode *parent;
		friend class BSTree;
	public:
		BSTNode(double k = 0.0, BSTNode *l = nullptr, BSTNode *r = nullptr, BSTNode *p = nullptr
		       ): key(k), lchild(l), rchild(r), parent(p) {
		}
};

class BSTree
{
	private:
		BSTNode *root;
		
		void inorder_tree_walk(BSTNode *t) {
	if (t != nullptr) {
		inorder_tree_walk(t->lchild);
		cout << t->key << " ";
		inorder_tree_walk(t->rchild);
	}
}

void preorder_tree_walk(BSTNode *t) {
	if (t != nullptr) {
		cout << t->key << " ";
		preorder_tree_walk(t->lchild);
		preorder_tree_walk(t->rchild);
	}
}

void postorder_tree_walk(BSTNode *t) {
	if(t!=nullptr)
	{
	postorder_tree_walk(t->lchild);
	postorder_tree_walk(t->rchild);
	cout << t->key << " ";
}
}


BSTNode *tree_search_one(BSTNode *t, double k) {
	if (t == nullptr || k == t->key)
		return t;

	if (k < t->key)
		return 	tree_search_one(t->lchild,k);
	else
		return tree_search_one(t->rchild,k);
}

BSTNode *tree_search_two(BSTNode *t,double k)
{
	while(t!=nullptr && k!=t->key)
	{
		if (k < t->key)
			t = t->lchild;
		else t = t->rchild;
	}
	return t;
}


BSTNode *tree_min(BSTNode *t)
{
	while(t->lchild!=nullptr)
	t = t->lchild;
	return t;
}

BSTNode *tree_max(BSTNode *t)
{
	while(t->rchild!=nullptr)
		t = t->rchild;
	return t;
}

BSTNode *tree_successor(BSTNode *t)
{
	BSTNode *y;
	if (t->rchild!=nullptr) return tree_min(t->rchild);
	y = t->parent;
	while(y!=nullptr && t==y->rchild)
	{
		t = y;
		y = y->parent;
	}
	return y;
}

BSTNode *tree_predecessor(BSTNode *t)
{
	BSTNode *y;
	y = t->parent;
	if (t->lchild!=nullptr) return tree_max(t->lchild);
	while(y!=nullptr && t==y->lchild)
	{
		t = y;
		y = y->parent;
	}
	return y;
}


void tree_insert(BSTNode *&t,BSTNode *z)
{
	BSTNode *x = t;
	BSTNode *y = nullptr;
	while(x!=nullptr)
	{
		y = x;
		if (z->key < x->key) x = x->lchild;
		else x = x->rchild;
	}
	z->parent = y;
	if (y==nullptr) t = z;
	else if (z->key < y->key) y->lchild = z;
	else y->rchild = z;
}

void transplant(BSTNode *&t,BSTNode *u,BSTNode *v)
{
	if (u->parent==nullptr) t = v;
	else if (u->parent->lchild==u) u->parent->lchild = v;
	else u->parent->rchild = v;
	if (v!=nullptr) v->parent = u->parent;
}

BSTNode *tree_delete(BSTNode *&t,BSTNode *z)
{
	BSTNode *y = nullptr;
	if(z->lchild==nullptr) transplant(t,z,z->rchild);
	else if (z->rchild==nullptr) transplant(t,z,z->lchild);
	else
	{
		y = tree_min(z->rchild);
		if (y->parent!=z)
		{
			transplant(t,y,y->rchild);
			y->rchild = z->rchild;
			y->rchild->parent = y;
		}
		transplant(t,z,y);
		y->lchild = z->lchild;
		y->lchild->parent = y;
	}
	return z;
}
	void tree_destory(BSTNode *&t)
	{
		if(t==nullptr) return ;
		if (t->lchild!=nullptr) return tree_destory(t->lchild);
		if (t->rchild!=nullptr) return tree_destory(t->rchild);
		
		delete t;
		t = nullptr;
	}
	public:
		BSTree():root(nullptr){
		}
		
	void PreOrder_Tree_Walk()
	{
		preorder_tree_walk(root);
		cout<<endl;
	}
	
	void InOrder_Tree_Walk()
	{
		inorder_tree_walk(root);
		cout<<endl;
	}
	
	void PostOrder_Tree_Walk()
	{
		postorder_tree_walk(root);
		cout<<endl;
	}
	
	BSTNode *Tree_Search(double key)
	{
		return tree_search_one(root,key);
	}
	
	BSTNode *Iterative_Tree_Search(double key)
	{
		return tree_search_two(root,key);
	}
	
	BSTNode* Tree_Minimum(BSTNode *x)
	{
		return tree_min(x);				
	}
 
	BSTNode* Tree_Maximum(BSTNode *x)
	{
		return tree_max(x);					
	}
	
	BSTNode *Tree_Successor(BSTNode *x)
	{
		return tree_successor(x);
	}
	
	BSTNode *Tree_Predecessor(BSTNode *x)
	{
		return tree_predecessor(x);
	}
	
	void Tree_Insert(double key)
	{
		BSTNode *z = new BSTNode(key,nullptr,nullptr,nullptr);
		if (z==nullptr) return ;
		
		tree_insert(root,z); 
	}
	
	void Tree_Delete(double key)
	{
		BSTNode *z,*node;
		z = tree_search_two(root,key);
		if (z!=nullptr)
		{
			node = tree_delete(root,z);
			if (node !=nullptr){
				delete node;
				node = nullptr;
			}
		}
	}
	
	void Tree_Destory()
	{
		tree_destory(root);
	}
	
	~BSTree()
	{
		Tree_Destory();
	}
};


int main()
{
	int i,j,n;
	double *arr;
	BSTree *tree = new BSTree();
	
	cout<<"请输入节点/关键字个数:"<<endl;
	cin>>n;
	arr = new double[n];
	
	cout<<"请依次输入关键字(注意每棵子树的根节点都要比它的孩子结点先输入): "<<endl;
	for (int i = 0;i<n;i++)
	{
		cin>>arr[i];
		tree->Tree_Insert(arr[i]);
	}
	cout<<endl;
	cout << "二叉搜索树先序遍历的结果为: ";
	tree->PreOrder_Tree_Walk();
	cout << "二叉搜索树中序遍历的结果为: ";
	tree->InOrder_Tree_Walk();
	cout << "二叉搜索树后序遍历的结果为: ";
	tree->PostOrder_Tree_Walk();
	cout << endl;
	
	double seakey;
	cout<<"请输入要查找的节点关键字:"<<endl;
	cin>>seakey;
	BSTNode *seaNode  = tree->Tree_Search(seakey);
	if (seaNode) cout<<"查找成功!"<<endl;
	else 		cout << "查找失败, 关键字为" << seakey << "的结点不存在" << endl;
	cout<<endl;
		double delkey;
	cout << "请输入要删除的结点关键字: " << endl;
	cin >> delkey;
	tree->Tree_Delete(delkey);
	
	// 通过先序与中序遍历，或者中序与后序遍历可以唯一确定一棵二叉树
	// 因此此处可以验证删除后的二叉搜索树是否与你预想的一样
	cout << "删除操作后先序遍历二叉搜索树的结果为: ";
	tree->PreOrder_Tree_Walk();
	cout << "删除操作后中序遍历二叉搜索树的结果为: ";
	tree->InOrder_Tree_Walk();
	cout << endl;
	
		tree->Tree_Destory();				// 销毁二叉树
	delete[] arr;
 
	system("pause");
 
	return 0;
}

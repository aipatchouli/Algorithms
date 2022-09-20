#include<bits/stdc++.h>
using namespace std;

void add(int newNum);
int maxXor(int eorj);
int maxXorSubarray2(vector<int> &arr);

class Node { // 一颗 前缀树 表示的 一个数字
	public:
		Node *nexts[2] = {NULL};// 前缀树 两个分支 0 / 1
};

Node *head = new Node();

void add(int newNum) {
	Node *cur = head;
	for (int move = 31; move >= 0; move--) {
		int path = ((newNum >> move) & 1); //从最大的 位 开始 0 或 1
		cur->nexts[path] = cur->nexts[path] == NULL ? new Node() : cur->nexts[path];
		cur = cur->nexts[path];
	}
}

int maxXor(int eorj) {
	Node *cur = head;
	int res = 0;
	for (int move = 31; move >= 0; move--) {
		int path = (eorj >> move) & 1; //取位的值
		int best = move == 31 ? path : (path ^ 1);//最期待的 值 符号位希望相同->正数 其他位->取反
		best = cur->nexts[best] != NULL ? best : (best ^ 1);//有则走，无则妥协
		res |= (path ^ best) << move; // 当前位 异或的 最佳结果
		cur = cur->nexts[best];//去下一位
	}
	return res;
}

int maxXorSubarray2(vector<int> &arr) {
	if (arr.empty() || arr.size() == 0) {
		return 0;
	}
	int mx = numeric_limits<int>::min();
	int eor = 0;
	add(0); //刚开始 没有计算 异或和==0
	for (int j = 0; j < arr.size(); j++) {
		eor ^= arr[j];
		mx = max(mx, maxXor(eor));//前缀数里装着 0-1 0-2 0-(j-1)
		add(eor);
	}
	return mx;
}

int main() {
	vector<int> arr {3, -28, -29, 2};
	int res = maxXorSubarray2(arr);
	cout << res << endl;
	return 0;
}
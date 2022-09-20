#include<bits/stdc++.h>
using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BFPRT{
public:
	// 时间复杂度 T(N) = T(N/2) + O(N) = O(N)
	int getMinKthByBFPRT(vector<int>& arr, int k, int left, int right) {
		if (arr.empty() || k >= arr.size() || left > right || k < left || k > right) {
			return -1;
		}
		if (left == right) {
			return arr.at(left);
		}
		// 获取每组的中位数组成的数组的中位数(这是BFPTR算法与荷兰国旗问题最大的不同点)
		// 时间复杂度 O(N)
		int pivot = medianOfMedians(arr, left, right);
		// partition过程 <在左，=在中，>在右
		// 时间复杂度 O(N)
		vector<int> range = partition(arr, left, right, pivot);
		// k恰好在 相等的区域内，直接返回
		if (k > range.at(0) && k < range.at(1)) {
			return arr.at(k);
		}
		// 根据k所在的范围继续递归
		return k <= range.at(0) ? getMinKthByBFPRT(arr, k, left, range.at(0)) :
			getMinKthByBFPRT(arr, k, range.at(1), right);
	}

	// partition过程 <在左，=在中，>在右，时间复杂度 O(N)
	vector<int> partition(vector<int>& arr, int left, int right, int pivot) {
		int tmpL = left - 1;
		int tmpR = right + 1;
		int index = left;
		while (index < tmpR) {
			if (arr.at(index) < pivot) {
				swap(arr, index++, ++tmpL);
			}
			else if (arr.at(index) > pivot) {
				swap(arr, index, --tmpR);
			}
			else {
				index++;
			}
		}
		vector<int> res{ tmpL, tmpR };
		return res;
	}

	// 获取每组的中位数组成的数组的中位数，时间复杂度 O(N)
	int medianOfMedians(vector<int>& arr, int left, int right) {
		vector<int> medians;
		int offset = ((right - left + 1) % 5 == 0) ? 0 : 1;
		int groupNums = (right - left + 1) / 5 + offset;
		// 此过程 (N/5) * O(1) = O(N)，(N/5)次5个数(或少于5个)排序O(1)
		for (int i = 0; i < groupNums; i++) {
			int tmpL = left + i * 5;
			int tmpR = tmpL + 5;
			sort(arr.begin() + tmpL, arr.begin() + min(tmpR, right));
			medians.push_back(arr.at(tmpL + ((min(tmpR, right) - tmpL) >> 1)));
		}
		return getMinKthByBFPRT(medians, medians.size() / 2, 0, medians.size() - 1);
	}

	void swap(vector<int>& arr, int n1, int n2) {
		int tmp = arr.at(n1);
		arr.at(n1) = arr.at(n2);
		arr.at(n2) = tmp;
	}
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0;
        int right = nums.size()-1;
        // 返回排序情况下，k-1位置上的数
        return bfprt(nums, left, right, k-1);
    }
    int bfprt(vector<int>& nums, int left, int right, int k) {
        if (left == right) {
            return nums[left];
        }
        // 精挑细选一个数（上中位数）
        int pivot = midOfMids(nums, left, right);
        int index = partition(nums, left, right, pivot);
        if (index == k) {
            return nums[index];
        } else if (index < k) {
            left = index+1;
            return bfprt(nums, left, right, k);
        } else {
            right = index-1;
            return bfprt(nums, left, right, k);
        }
    }
    int midOfMids(vector<int>& nums, int left, int right) {
        int size = right - left + 1;
        int offset = size % 5 == 0 ? 0 : 1;
        int len =  size / 5 + offset;
        vector<int> midarr(len, 0);
        for (int i = 0; i < len; ++i) {
            int start = left + i*5;
            int end = min(right, start+4);
            // 在c++的sort函数中，迭代器是指针需要移动的步数，所以要移动5步
            // 调用sort不要忘了加谓词，从大到小
            sort(nums.begin()+start, nums.begin()+end+1, greater());
            int retIdx = (start+end) / 2;
            midarr[i] = nums[retIdx];
        }
        return bfprt(midarr, 0, len-1, (len-1)/2);
    }
    int findIdx(vector<int>& nums, int pivot) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == pivot) {
                return i;
            }
        }
        return -1;
    }
    int partition(vector<int>& nums, int left, int right, int pivot) {
        int std = findIdx(nums, pivot);
        swap(nums[left], nums[std]);
        int index = left+1;
        for (int i = index; i <= right; ++i) {
            if (nums[i] >= nums[left]) {
                swap(nums[i], nums[index]);
                index++;
            }
        }
        swap(nums[left], nums[index-1]);
        return index-1;
    }
};

int main() {
	vector<int> arr{ 2,3,1,5,6,4 };
	cout << BFPRT().getMinKthByBFPRT(arr, 2, 0, arr.size() - 1) << endl;

	return 0;
}

#include<bits/stdc++.h>
using namespace std;

class BubbleSort{ //稳定
public:
    // arr 为需要被排序的数组
    void bubble_sort(vector<int>& arr, const int l, const int r) {
        for (int i = l; i < r; i++) {
            for (int j = l; j < r - i + l; j++) {
                if (arr[j] > arr[j+1]) {
                    swap(arr[j], arr[j+1]);
                }
            }
        }
    }
};

class SelectionSort{ // 不稳定
public:
    // arr 为需要被排序的数组
    void selection_sort(vector<int>& arr, const int l, const int r) {
        for (int i = l; i < r; i++) {
            int min_index = i;
            for (int j = i + 1; j <= r; j++) {
                if (arr[j] < arr[min_index]) {
                    min_index = j;
                }
            }
            swap(arr[i], arr[min_index]);
        }
    }
};

class InsertionSort{ // 稳定
public:
    // arr 为需要被排序的数组
    void insertion_sort(vector<int>& arr, const int l, const int r) {
        for (int i = l + 1; i <= r; i++) {
            int j = i;
            while (j > l && arr[j] < arr[j-1]) {
                swap(arr[j], arr[j-1]);
                j--;
            }
        }
    }
};

class ShellSort{ // 变种插入排序 不稳定
public:
    // arr 为需要被排序的数组
    void shell_sort(vector<int>& arr, const int l, const int r) {
        int gap = r - l + 1;
        while (gap > 1) {
            gap = gap / 3 + 1;
            for (int i = l + gap; i <= r; i++) {
                int j = i;
                while (j - gap >= l && arr[j] < arr[j-gap]) {
                    swap(arr[j], arr[j-gap]);
                    j -= gap;
                }
            }
        }
    }
};


class Quicksort{ // 不稳定
public:
    // arr 为需要被排序的数组
    void quick_sort(vector<int>& arr, const int l, const int r) {
        if (l >= r) 
            return;
        // 随机选择基准（pivot）
        const int pivot = arr[l + rand() % (r-l+1)];
        // const int pivot = arr[l];
        // i：当前操作的元素
        // lt：第一个等于 pivot 的元素
        // gt：第一个大于 pivot 的元素
        int i = l, lt = l, gt = r;
        // 完成一趟三路快排，将序列分为：
        // 小于 pivot 的元素｜ 等于 pivot 的元素 ｜ 大于 pivot 的元素
        while (i <= gt) {
            if (arr[i] < pivot)
                swap(arr[i++], arr[lt++]);
            else if (pivot < arr[i])
                swap(arr[i], arr[gt--]);
            else
                i++;
        }
        // 递归完成对于两个子序列的快速排序
        quick_sort(arr, l, lt-1);
        quick_sort(arr, gt+1, r);
    }
};

// iParent(i) = (i - 1) / 2;
// iLeftChild(i) = 2 * i + 1;
// iRightChild(i) = 2 * i + 2;
class Heapsort{ // 不稳定
public:
    // arr 为需要被排序的数组
    void heap_sort(vector<int>& arr, const int l, const int r) {
        int len = r - l + 1;
        // 从最后一个节点的父节点开始 sift down 以完成堆化 (heapify)
        for (int i = (len - 1 - 1) / 2; i >= 0; i--) 
            sift_down(arr, i, len - 1);
        // 先将第一个元素和已经排好的元素前一位做交换，再重新调整（刚调整的元素之前的元素），直到排序完毕
        for (int i = len - 1; i > 0; i--) {
            swap(arr[0], arr[i]); // 最大元素逐渐下沉
            sift_down(arr, 0, i - 1);
        }
    }   
private:
    void sift_down(vector<int>& arr, int start, int end) {
        // 计算父结点和子结点的下标
        int parent = start;
        int child = parent * 2 + 1;
        while (child <= end) {  // 子结点下标在范围内才做比较
            // 先比较两个子结点大小，选择最大的
            if (child + 1 <= end && arr[child] < arr[child + 1]) 
                child++;
            // 如果父结点比子结点大，代表调整完毕，直接跳出函数
            if (arr[parent] >= arr[child])
                return;
            else {  // 否则交换父子内容，子结点再和孙结点比较
                swap(arr[parent], arr[child]);
                parent = child;
                child = parent * 2 + 1;
            }
        }
    }
};


class Mergesort{ // 考虑越界，l=0, r=len  // 稳定
public:
    // arr 为需要被排序的数组
    void merge_sort_1(vector<int>& arr, const int l, const int r) {
        if (r - l <= 1) 
            return;
        int mid = l + ((r - l) >> 1);
        merge_sort_1(arr, l, mid);
        merge_sort_1(arr, mid, r);

        vector<int> tmp (r-l+1);
        for (int i = l, j = mid, k = 0; k < r-l; ++k) {
            if (j == r || (i < mid && arr[i] <= arr[j]))
                tmp[k] = arr[i++];
            else
                tmp[k] = arr[j++];
                // if (i < mid) ans += mid - i ; 统计逆序对
        }
        for (int i = l; i < r; ++i) 
            arr[i] = tmp[i-l];
    }

    void merge_sort_2(vector<int>& arr, vector<int>& tmp, const int l, const int r) {
        if (r - l <= 1) 
            return;
        int mid = l + ((r - l) >> 1);
        merge_sort_2(arr, tmp, l, mid);
        merge_sort_2(arr, tmp, mid, r);

        for (int i = l, j = mid, k = l; k < r; ++k) {
            if (j == r || (i < mid && arr[i] <= arr[j])) {
                tmp[k] = arr[i++];
            } else {
                tmp[k] = arr[j++];
                // if (i < mid) ans += mid - i; 统计逆序对
            }
        }
        for (int i = l; i < r; ++i) 
            arr[i] = tmp[i];
    }
};



int main() {
    int N = 20;
    vector<int> ran_list (N);
    for (int i=0; i<N; i++) {
        ran_list[i] = rand() % N;
        cout << ran_list[i] << " ";
    }
    cout << endl;
    // Quicksort sort;
    // sort.quick_sort(ran_list, 0, N-1);
    // for (const auto& x : ran_list) {
    //     cout << x << " ";
    // }
    // cout << endl;

    // Heapsort sort;
    // sort.heap_sort(ran_list, 0, N-1);
    // for (const auto& x : ran_list) {
    //     cout << x << " ";
    // }
    // cout << endl;

    /* vector<int> tmp (N);
    Mergesort sort;
    sort.merge_sort_2(ran_list, tmp, 0, N); */

    /* BubbleSort sort;
    sort.bubble_sort(ran_list, 0, N-1); */

    /* SelectionSort sort;
    sort.selection_sort(ran_list, 0, N-1); */

    /* InsertionSort sort;
    sort.insertion_sort(ran_list, 0, N-1); */

    ShellSort sort;
    sort.shell_sort(ran_list, 0, N-1);
    for (const auto& x : ran_list) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
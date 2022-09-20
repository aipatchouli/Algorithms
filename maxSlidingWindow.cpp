#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int len = nums.size();
        //双端队列 严格单调 大->小
        deque<int> qmax;
        vector<int> res;

        int l = 0;
        //r 往右动
        for (int r = 0; r < len; r++) {
            //非空 且 不满足 严格单调
            while (!qmax.empty() && nums[qmax.back()] <= nums[r]) {
                qmax.pop_back();
            }
            qmax.push_back(r);
            //l 往右动 保持 k 大小
            if (qmax.front() == r-k) {
                qmax.pop_front();
            }
            //应为单调，窗口中最大值为当前的 front
            if (r >= k-1) {
                res.push_back(nums[qmax.front()]);
            }
        }
        return res;
    }
};
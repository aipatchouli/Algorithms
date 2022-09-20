#include<bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    int cap;
    list<int> lru; // key, key的迭代器, 逻辑主体，存储key
    unordered_map<int, int> cache; // 通过key找value
    unordered_map<int, list<int>::iterator> lru_map; // 通过key在lru中找到对应的迭代器，方便删除，更新，插入，查找，O(1)
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    ~LRUCache() {
        lru.clear();
        cache.clear();
        lru_map.clear();
    }
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        // 更新lru
        lru.erase(lru_map[key]);
        lru.push_front(key);
        lru_map[key] = lru.begin();
        return cache[key];
    }
    
    void put(int key, int value) {
        // 更新lru
        if (cache.find(key) != cache.end()) {
            cache[key] = value;
            lru.erase(lru_map[key]);
            lru.push_front(key);
            lru_map[key] = lru.begin();
            return;
        }
        // 越界处理
        if (lru.size() == cap) {
            int last = lru.back();
            lru.pop_back();
            lru_map.erase(last);
            cache.erase(last);
        }
        // 插入
        lru.push_front(key);
        lru_map[key] = lru.begin();
        cache[key] = value;
    }
};
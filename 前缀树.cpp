#include<bits/stdc++.h>
using namespace std;

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
class Trie {
private:
    Trie* son[26];//分支
    bool isWord;
public:
    Trie() {
        isWord = false;
        for(int i = 0; i < 26; i++) 
            son[i] = nullptr;
    }
    
    ~Trie(){
        for(int i = 0; i < 26 ; i++){
            if(son[i] != nullptr) 
                delete son[i];
        }
    }

    void insert(string word) {
        Trie* root = this;
        for(char x: word){
            int cur = x - 'a';
            if(root->son[cur] == nullptr) 
                root->son[cur] = new Trie();
            root = root->son[cur];
        }
        root->isWord = true;
    }
    
    bool search(string word) {
        Trie* root = this;
        for(char x : word){
            int cur = x - 'a';
            if(root->son[cur] == nullptr) 
                return false;
            root = root->son[cur];
        }
        return root->isWord;
    }
    
    bool startsWith(string prefix) {
        Trie* root = this;
        for(char x : prefix){
            int cur = x - 'a';
            if(root->son[cur] == nullptr) 
                return false;
            root = root->son[cur];
        }
        return true;
    }
};

int main() {

    return 0;
}
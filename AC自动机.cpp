#include<bits/stdc++.h>
using namespace std;

class StreamChecker {
public:
    struct TrieNode {
        TrieNode* next[26];
        bool isWord;
        TrieNode():isWord(false) {
            for (int i=0;i<26;i++)
                next[i]=NULL;
        }
    };
    TrieNode* root;
    string buffer;
    int maxlen;
    StreamChecker(vector<string>& words) {
        root=new TrieNode();
        maxlen=0;
        for (string word:words) {
            TrieNode* node=root;
            for (int i=word.length()-1;i>=0;i--) {
                if (node->next[word[i]-'a']==NULL)
                    node->next[word[i]-'a']=new TrieNode();
                node=node->next[word[i]-'a'];
            }
            node->isWord=true;
            maxlen=max(maxlen,(int)word.length());
        }
    }
    
    bool query(char letter) {
        buffer+=letter;
        if (buffer.length()>maxlen)
            buffer=buffer.substr(buffer.length()-maxlen);
        TrieNode* node=root;
        for (int i=buffer.length()-1;i>=0;i--) {
            if (node->next[buffer[i]-'a']==NULL)
                return false;
            node=node->next[buffer[i]-'a'];
            if (node->isWord)
                return true;
        }
        return false;
    }
};


int main() {
    string inputs[]={"ab","ba","aaab","abab","baa"};
    vector<string> words(inputs,inputs+5);
    StreamChecker* checker=new StreamChecker(words);
    cout << "000001111100111100011111101110" << endl << endl;
    string testinput="aaaaabababbbababbbbababaaabaaa";
    for (char c:testinput)
        cout << checker->query(c);
    delete checker;
    cout << endl;
}
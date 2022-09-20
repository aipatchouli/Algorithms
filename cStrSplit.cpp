#include<bits/stdc++.h>
using namespace std;

std::vector<std::string> splitStrtok(std::string str, std::string delim) {
    char* s = str.data();
    char* d = delim.data();
    std::vector<std::string> res;
    char *p;
    p = strtok(s, d);
    while(p) {
        res.push_back(p);
        p = strtok(nullptr, d);
    }
    return res;
}

int main() {
    string s = "Golden Global   C\\E  View,disk * desk";
    string d = " ,*";
    std::vector<std::string> str_vec = splitStrtok(s, d);
    for (const auto& x: str_vec) {
        cout << x << endl;
    }
    cout << s << endl;
    return 0;
}
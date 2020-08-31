#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


vector<string> SplitIntoWords(const string& s){
    vector<string> result;
    result.push_back(string(begin(s), find(begin(s), end(s), ' ')));
    for (auto it = find(begin(s), end(s), ' '); it != end(s); it = find(next(it), end(s), ' ')) {
        result.push_back(string(it+1, next(it)));
    }
    return result;
}

int main() {
    string s = "C Cpp Java Python";
 
    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;
 
    return 0;
}
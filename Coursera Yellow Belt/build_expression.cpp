#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <deque>

using namespace std;

int main(){
    deque<string> q;
    int start, N;
    int c;
    string s;
    cin >> start >> N;
    if (N==0){
        cout << start;
    }else{
        q.push_back("(" + to_string(start) + ")");
        for (int i = 1; i < N; ++i){
            q.push_front("(");
            cin >> s >> c;
            q.push_back(" " + s + " " + to_string(c) + ")");
        }
        cin >> s >> c;
        q.push_back(" " + s + " " + to_string(c));
        for (string& i : q){
            cout << i;
        }

    }

    return 0;
}
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
    int start, N, num;
    string s, prev_s;
    cin >> start;
    cin >> N;
    q.push_back(to_string(start));
    for (int i=1; i <= N; ++i){
        cin >> s >> num;
        if ((s == "/" || s == "*" ) && (prev_s == "-" || prev_s == "+")){
            q.push_front("(");
            q.push_back(") " + s + " "+to_string(num));
        }else{
            q.push_back(" " + s +" " + to_string(num));
        }
        prev_s = s;
    }



    for (string& i :q){
        cout << i;
    }
    return 0;
}
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


int main(){
    int N;
    cin >> N;
    vector<int> num;
    for (int i = N; i > 0; --i){
        num.push_back(i);
    }
    do {
       for ( auto i : num){
           cout << i << ' ';
       }
       cout << endl;
    } while(prev_permutation(num.begin(), num.end()));
}
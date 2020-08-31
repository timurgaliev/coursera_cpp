#include "sum_reverse_sort.h"
#include <iostream>
using namespace std;
#include <algorithm>

int Sum(int x, int y){
    return x+y;
}
string Reverse(string s){
    string rev = s;
    reverse(rev.begin(), rev.end());
    return rev;
}
void Sort(vector<int>& nums){
    sort(nums.begin(), nums.end());
}

int main(){
    int x = 1;
    int y = 4;
    vector<int> sort = {5,4,7,5,4,8};
    string s = "bcda";

    int z = Sum(x,y);

    Sort(sort);
    Reverse(s);
    cout << z;


    return 0;
}


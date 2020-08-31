#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


int main(){
  string s = "Timur Galiev t h r";
  vector<string::iterator> space;
  for (auto it = find(begin(s), end(s), ' '); it != end(s); it = find(next(it), end(s), ' ')) {
    space.push_back(it);
  }
  
  return 0;
}
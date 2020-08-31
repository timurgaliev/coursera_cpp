#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include<string>
#include <deque>

using namespace std;

int main(){
   deque<string> q;
   q.push_back("gg");
   q.push_back("rr");
   q.push_front("aa");
   for (string& i : q){
      cout << i << " ";
   }
   return 0;
}
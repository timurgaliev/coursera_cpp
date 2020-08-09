#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <ctype.h>
using namespace std;



int main(){
	int q;
	cin >> q;
	vector<string> s;
	for (int i=0; i<q; ++i){
		string temp;
		cin >> temp;
		s.push_back(temp);
	}
	sort(begin(s), end(s), [](string a, string b){
		string re_a, re_b;
		for( char j: a){
			re_a += tolower(j);
		}
		for (char j: b){
			re_b += tolower(j);
		}
		return re_a < re_b;

	});

	for (const auto& c: s){
		cout << c << " ";
	}


	return 0;
}

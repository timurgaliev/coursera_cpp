#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;



int main(){
	int q;
	cin >> q;
	map<string, set<string>> words;

	for( int i = 0; i < q; ++i){

		string command;
		cin >> command;

		if ( command == "ADD"){
			string f, s;
			cin >> f >> s;
			words[f].insert(s);
			words[s].insert(f);
		}
		else if ( command == "COUNT"){
			string word;
			cin >> word;
			cout << words[word].size() << endl;
		}
		else if (command == "CHECK"){
			string f, s;
			cin >> f >> s;
			if (words[f].count(s) == 1){
				cout << "YES" << endl;
			}
			else{
				cout << "NO" << endl;
			}

		}

	}

	return 0;
}

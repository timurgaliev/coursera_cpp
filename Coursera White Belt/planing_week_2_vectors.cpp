#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
	int q;
	cin >> q;
	vector<int> days_in_month = { 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31 };
	int current_month = 1;
	int current_days_in_month = days_in_month[current_month];

	vector<vector<string>> tag(current_days_in_month);

	for (int i = 0; i < q; ++i){

		string command = "";
		cin >> command;

		if (command == "ADD"){
			int day = 0;
			string name = "";
			cin >> day >> name;
			tag[day-1].push_back(name);
		}

		else if (command == "DUMP"){
			int day = 0;
			cin >> day;
			cout << tag[day-1].size() << " ";
			for (auto i: tag[day-1]){
				cout << i << " ";
			}
			cout << endl;
		}

		else if (command == "NEXT"){
			current_month ++;
			if (current_month > 12){
				current_month = 1;
			}

			//cout << days_in_month[current_month]<< endl;

			if (days_in_month[current_month] <= days_in_month[current_month - 1]){

				for (int i = days_in_month[current_month]; i < days_in_month[current_month -1]; ++i ){

					tag[days_in_month[current_month] -1].insert(end(tag[days_in_month[current_month] -1]), begin(tag[i]), end(tag[i]));
					tag[i].clear();

				}

			}

		}

	}


	return 0;
}

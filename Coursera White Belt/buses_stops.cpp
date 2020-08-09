#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;



int main() {
	int q;
	cin >> q;
	map<string, vector<string>> bus_stop;
	vector<string> exist_buses;

	for (int i = 0; i < q; ++i){

		string command;
		cin >> command;

		if (command == "NEW_BUS"){
			string bus;
			int stop_count;
			cin >> bus >> stop_count;
			exist_buses.push_back(bus);

			for (int j = 0; j < stop_count; ++j){
				string stop;
				cin >> stop;

				bus_stop[bus].push_back(stop);
			}
		}
		else if (command == "STOPS_FOR_BUS"){
			string bus;
			cin >> bus;
			if (bus_stop[bus].size() == 0){
				cout << "No bus" << endl;
				bus_stop.erase(bus);
			}else{
			for (auto item: bus_stop[bus]){
				vector<string> current_buses_stops;
				for (auto it: exist_buses){
					for (auto itt: bus_stop[it]){
						if (item == itt){
							current_buses_stops.push_back(it);
						}
					}
				}

				cout << "Stop " << item << ": ";
				for (auto a: current_buses_stops ){
					if ( current_buses_stops.size() == 1){
						cout << "no interchange";
					}
					else if (a!=bus){
						cout << a << " ";
					}
				}
				cout << endl;

			}

		}
		}

		else if (command == "BUSES_FOR_STOP"){

			string stop;
			cin >> stop;
			vector<string> current_buses_for_stop;

			for  ( auto item: exist_buses ){
				for ( auto it: bus_stop[item]){
					if ( it == stop){
						current_buses_for_stop.push_back(item);
					}
				}
			}
			if (current_buses_for_stop.size() == 0){
				cout << "No stop" << endl;
			}else{
				//cout << "Stop " << stop << ": ";
				for ( auto i: current_buses_for_stop){
					cout << i << " ";
				}
				cout << endl;
			}
		}
		else if ( command == "ALL_BUSES"){
			if (bus_stop.size() == 0){
				cout << "No buses" << endl;
			}
			for (auto item: bus_stop){
				cout << "Bus " << item.first <<": ";
				for (auto it: item.second){
					cout << it << " ";
				}
				cout << endl;
			}
		}
	}
	return 0;
}

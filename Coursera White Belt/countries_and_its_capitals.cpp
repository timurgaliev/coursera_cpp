#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;


void CHANGE_CAPITAL(const string& country, const string& new_capital, map<string, string>& countries_and_capitals){

	if ( countries_and_capitals.count(country) == 0){
		cout << "Introduce new country " << country <<  " with capital " << new_capital<< endl;
		countries_and_capitals[country] = new_capital;
	}
	else if (countries_and_capitals.count(country) != 0 && countries_and_capitals[country] == new_capital){
		cout << "Country " << country << " hasn't changed its capital" << endl;
	}
	else if (countries_and_capitals.count(country) != 0 && countries_and_capitals[country] != new_capital){
		cout << "Country " << country << " has changed its capital from " << countries_and_capitals[country] << " to " << new_capital << endl;
		countries_and_capitals.erase(country);
		countries_and_capitals[country] = new_capital;
	}
}


void RENAME(const string& old_country_name, const string& new_country_name, map<string, string>& countries_and_capitals){

	map<string,string >rev_countries_and_capitals;
	for (auto& items: countries_and_capitals){
		rev_countries_and_capitals[items.second] = items.first;
	}

	if (countries_and_capitals.count(old_country_name) == 0 || countries_and_capitals.count(new_country_name) != 0 || rev_countries_and_capitals[countries_and_capitals[old_country_name]] == new_country_name  ){
		cout <<"Incorrect rename, skip"<< endl;
	}else{
		string new_country_old_capital = countries_and_capitals[old_country_name];
		countries_and_capitals.erase(old_country_name);
		countries_and_capitals[new_country_name] = new_country_old_capital;
		cout << "Country " << old_country_name << " with capital " <<  new_country_old_capital << " has been renamed to " << new_country_name << endl;
	}
}




int main() {
	int q;
	cin >> q;
	map<string, string> countries_and_capitals;

	for ( int i = 0; i < q; ++i){

		string command;
		cin >> command;

		if (command == "CHANGE_CAPITAL"){
			string country, new_capital;
			cin >> country >> new_capital;
			CHANGE_CAPITAL(country,new_capital, countries_and_capitals);

		}
		else if (command == "RENAME"){
			string old_country_name, new_country_name;
			cin >> old_country_name >> new_country_name;
			RENAME(old_country_name, new_country_name, countries_and_capitals);
		}
		else if (command == "ABOUT"){
			string country;
			cin >> country;
			if (countries_and_capitals.count(country) == 0){
				cout << "Country " << country << " doesn't exist" << endl;
			}else{
				cout << "Country " << country << " has capital " << countries_and_capitals[country] << endl;
			}
		}
		else if (command == "DUMP"){
			if (countries_and_capitals.size() == 0){
				cout << "There are no countries in the world" << endl;
			}else{
				for (auto& items: countries_and_capitals){
					cout << items.first << "/" << items.second << " ";
				}
			}
		}

	}

	return 0;
}

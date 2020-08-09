#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <ctype.h>
using namespace std;

// ���� ��� ����������, ���������� ������ ������
string FindNameByYear(const map<int, string>& names, int year) {
    string name;  // ���������� ��� ����������

    // ���������� ��� ������� �� ����������� ����� �������, �� ���� � ��������������� �������
    for (const auto& item : names) {
        // ���� ��������� ��� �� ������ �������, ��������� ���
        if (item.first <= year) {
            name = item.second;
        }
        else {
            // ����� ���� ������������, ��� ��� ��� ������ � ��� ����������� ��������� � ��������
            break;
        }
    }

    return name;
}

string FindHistoryNameByYear(const map<int, string>& names, int year) {
    vector<string> name_changing;
    string history = "";
    string current_name = "";
    string last_names = "";
    for (const auto& item: names){
    	if (year >= item.first){
    		name_changing.push_back(item.second);
    	}
    }
    if(!name_changing.empty()){
    	current_name = name_changing[name_changing.size() - 1];
    	if (name_changing.size() >= 3){
        	history += current_name;
    		for (int i = (name_changing.size()-2); i >= 1; --i){
    			if (name_changing[i] != name_changing[i+1]){
    				last_names += name_changing[i] + ", ";
    			}
    		}
    		if (name_changing[0] != name_changing[1]){
    		last_names += name_changing[0];
    		}
    		if (last_names.length() != 0){
    			history += " (" +last_names + ")";
    		}
    	}
    	else if(name_changing.size() == 2){
    		if (name_changing[1] != name_changing[0] ){
    			history = name_changing[1] + " (" + name_changing[0] + ")";
    	} else{
    		history = name_changing[0];
    	}
    	}
    	else{
    		history = name_changing[0];
    	}

    }
    return history;
}


class Person {
public:
	Person (const string& first_nam, const string& second_nam, const int& year){
		first_names[year] = first_nam;
		last_names[year] = second_nam;
	}
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }
    string GetFullName(int year) const {
        // �������� ��� � ������� �� ��������� �� ��� year
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);

        // ���� � ���, � ������� ����������
        if (first_name.empty() && last_name.empty()) {
            return "No person";

            // ���� ���������� ������ ���
        }
        else if (first_name.empty()) {
            return last_name + " with unknown first name";

            // ���� ���������� ������ �������
        }
        else if (last_name.empty()) {
            return first_name + " with unknown last name";

            // ���� �������� � ���, � �������
        }
        else {
            return first_name + " " + last_name;
        }
    }

    string GetFullNameWithHistory(int year) const {
        const string first_name_changing = FindHistoryNameByYear(first_names, year);
        const string last_name_changing = FindHistoryNameByYear(last_names, year);

        if (first_name_changing.empty() && last_name_changing.empty()){
        	return "No person";
        }
        else if (first_name_changing.empty()) {
            return last_name_changing + " with unknown first name";
        }
        else if (last_name_changing.empty()) {
            return first_name_changing + " with unknown last name";
        }
        else {
        	return first_name_changing + " " + last_name_changing;
        }

    }


private:
    map<int, string> first_names;
    map<int, string> last_names;
};

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}



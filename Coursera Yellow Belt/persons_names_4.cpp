#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace std;

string FindByYear(const map<int, string>& data, int year){
    auto it = data.upper_bound(year);
    string name;
    if (it != data.begin()){
        name = (--it) -> second;
    }
    return name;
}


class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    history_name[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    history_surname[year] = last_name;
  }
  string GetFullName(int year) {
    const string name = FindByYear(history_name, year);
    const string surname = FindByYear(history_surname, year);
    if (name.empty() && surname.empty()){
        return "Incognito";
    }
    else if (name.empty()){
        return surname + " with unknown first name";
    }
    else if (surname.empty()){
        return name + " with unknown last name";
    }else{
        return name + " " + surname;
    }

  }
private:
  map<int, string> history_name, history_surname;
};


int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}
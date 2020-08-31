#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    data_name[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    data_surname[year] = last_name;
  }
  string GetFullName(int year) {
    string current_name, current_surname;
    for (auto& [key, value]: data_name){
      if (key <= year){
        current_name = value;
      }else{
        break;
      }
    }
    for (auto& [key,value] : data_surname){
      if (key <= year){
        current_surname = value;
      }else{
        break;
      }
    }
    if (current_name.empty() && !current_surname.empty()){
      return current_surname + " with unknown first name";
    }
    else if (current_surname.empty() && !current_name.empty()){
      return current_name + " with unknown last name";
    }
    else if (current_name.empty() && current_surname.empty()){
      return "Incognito";
    }else{
      return current_name + ' ' + current_surname;
    }
  }
private:
  map<int, string> data_name, data_surname;
};

void TestIncognito(){
  Person person;
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  person.ChangeFirstName(1970, "Appolinaria");
  person.ChangeLastName(1968, "Volkova");
  AssertEqual(person.GetFullName(1900), "Incognito");
  AssertEqual(person.GetFullName(1915), "Incognito");
  AssertEqual(person.GetFullName(1945), "Incognito");
}
void TestOnlyName(){
  Person person;
  person.ChangeFirstName(1965, "Polina");
  person.ChangeFirstName(1970, "Appolinaria");
  AssertEqual(person.GetFullName(1965), "Polina with unknown last name");
  AssertEqual(person.GetFullName(1969), "Polina with unknown last name");
  AssertEqual(person.GetFullName(1983), "Appolinaria with unknown last name");
}
void TestOnlySurname(){
  Person person;
  person.ChangeLastName(1967, "Sergeeva");
  person.ChangeLastName(1968, "Volkova");
  AssertEqual(person.GetFullName(1967), "Sergeeva with unknown first name");
  AssertEqual(person.GetFullName(1968), "Volkova with unknown first name");
  AssertEqual(person.GetFullName(2000), "Volkova with unknown first name");
}
void TestFullName(){
  Person person;
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  person.ChangeFirstName(1970, "Appolinaria");
  person.ChangeLastName(1968, "Volkova");
  AssertEqual(person.GetFullName(1967), "Polina Sergeeva");
  AssertEqual(person.GetFullName(1968), "Polina Volkova");
  AssertEqual(person.GetFullName(1970), "Appolinaria Volkova");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIncognito, "Incognito");
  runner.RunTest(TestOnlyName, "Name");
  runner.RunTest(TestOnlySurname, "surname");
  runner.RunTest(TestFullName, "Full Name");
  
  return 0;
}

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

enum class Gender {
  FEMALE,
  MALE
};

struct Person {
  int age;  // возраст
  Gender gender;  // пол
  bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}

void PrintStats(vector<Person> persons){
    // median age
    int median_age = ComputeMedianAge(begin(persons), end(persons));
    cout << "Median age = " << median_age << endl;
    // Median age for females = 
    auto it1 = partition(begin(persons), end(persons), [](Person f){
        return f.gender == Gender::FEMALE;
    });
    int median_age_female = ComputeMedianAge(begin(persons), it1);
    cout << "Median age for females = " << median_age_female << endl;
    // Median age for males = 
    auto it2 = partition(begin(persons), end(persons), [](Person f){
        return f.gender == Gender::MALE;
    });
    int median_age_male = ComputeMedianAge(begin(persons), it2);
    cout << "Median age for males = " << median_age_male << endl;
    // Median age for employed females 
    auto it3 = partition(begin(persons), end(persons), [](Person f){
        return f.gender == Gender::FEMALE && f.is_employed;
    });
    int median_age_for_employed_females = ComputeMedianAge(begin(persons), it3);
    cout << "Median age for employed females = " << median_age_for_employed_females << endl;
    // Median age for unemployed females 
    auto it4 = partition(begin(persons), end(persons), [](Person f){
        return f.gender == Gender::FEMALE && !f.is_employed;
    });
    int median_age_for_unemployed_females = ComputeMedianAge(begin(persons), it4);
    cout << "Median age for unemployed females = " << median_age_for_unemployed_females << endl;
    // Median age for employed males 
    auto it5 = partition(begin(persons), end(persons), [](Person f){
        return f.gender == Gender::MALE && f.is_employed;
    });
    int median_age_for_employed_males = ComputeMedianAge(begin(persons), it5);
    cout << "Median age for employed males = " << median_age_for_employed_males << endl;
    // Median age for unemployed males 
    auto it6 = partition(begin(persons), end(persons), [](Person f){
        return f.gender == Gender::MALE && !f.is_employed;
    });
    int median_age_for_unemployed_males = ComputeMedianAge(begin(persons), it6);
    cout << "Median age for unemployed males = " << median_age_for_unemployed_males << endl;

}

int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}


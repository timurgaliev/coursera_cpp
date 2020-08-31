#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, string prefix){
    auto it1 = lower_bound(range_begin, range_end, prefix, [](auto s, string prefix){
        string t = "";
        for (int i =0; i < prefix.length(); ++i){
            t += s[i];
        }
        return t < prefix;
    });
    auto it2 = upper_bound(range_begin, range_end, prefix, [](string prefix, auto s){
        string t = "";
        for (int i =0; i < prefix.length(); ++i){
            t += s[i];
        }
        return t > prefix;
    }); 
    return make_pair(it1, it2);
}

int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  
  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}

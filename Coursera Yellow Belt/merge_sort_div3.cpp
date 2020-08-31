#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    if (range_end - range_begin >= 2){
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        auto it = begin(elements);
        advance(it, elements.size()/3);
        auto it2 = it; 
        advance(it2, elements.size()/3);
        MergeSort(begin(elements), it);
        MergeSort(it, it2);
        MergeSort(it2, end(elements));
        vector<typename RandomIt::value_type> temp;
        merge(begin(elements), it, it, it2, back_inserter(temp));
        merge(begin(temp), end(temp), it2, end(elements), range_begin);

    } 
}




int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
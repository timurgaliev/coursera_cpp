#pragma once
#include "date.h"
#include "condition_parser.h"
#include <map>
#include <set>
#include <vector>
#include <functional>
#include <iostream>
#include <iomanip>
#include <utility>

using namespace std;


class Database {
public:
    void Add(const Date& date, const string& event);
    int RemoveIf(const function<bool(const Date&, const string&)>& _pred);
    vector<pair<Date, string>> FindIf(const function<bool(const Date&, const string&)>& _pred) const;
    pair<Date, string> Last(const Date& date_) const;
    ostream& Print(ostream& output) const;
private:
    map<Date, set<string>> data;
    map<Date, vector<string>> data_vector;
};

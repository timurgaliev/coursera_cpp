#include "database.h"


void Database::Add(const Date& date, const string& event) {
    if (data[{date.GetYear(), date.GetMonth(), date.GetDay()}].count(event) != 1) {
        data_vector[{date.GetYear(), date.GetMonth(), date.GetDay()}].push_back(event);
    }
    data[{date.GetYear(), date.GetMonth(), date.GetDay()}].insert(event);
}

int Database::RemoveIf(const function<bool(const Date&, const string&)>& _pred) {
    int count = 0;
    map<Date, set<string>> new_data;
    map<Date, vector<string>> new_data_vector;
    if (!data_vector.empty()) {
        for (const auto& item : data_vector) {
            for (const auto& it : item.second) {
                if (_pred(item.first, it)) {
                    count += 1;
                }
                else {
                    new_data[item.first].insert(it);
                    new_data_vector[item.first].push_back(it);
                }
            }
        }
    }
    data = new_data;
    data_vector = new_data_vector;
    return count;
}

vector<pair<Date, string>> Database::FindIf(const function<bool(const Date&, const string&)>& _pred) const {
    vector<pair<Date, string>> find_result;
    if (!data_vector.empty()) {
        for (const auto& item : data_vector) {
            for (const auto& it : item.second) {
                if (_pred(item.first, it)) {
                    find_result.push_back(make_pair(item.first, it));
                }
            }
        }
    }
    return find_result;
}

pair<Date, string> Database::Last(const Date& date_) const {
    if (data_vector.empty() || date_ < begin(data_vector)->first) {
        throw invalid_argument("No entaries");
    }
    auto it = data_vector.equal_range(date_);
    if (it.first == end(data_vector) ) {
        --it.first;
    }
    else if (begin(data_vector) != it.first && it.first == it.second) {
        --it.first;
    }
    return make_pair(it.first->first, *rbegin(it.first->second));
}


ostream& Database::Print(ostream& output) const {
    if (!data_vector.empty()) {
        for (const auto& item : data_vector) {
            for (const auto& it : item.second) {
                output << fixed << setw(4) << setfill('0') << to_string(item.first.GetYear()) << '-' <<
                        setw(2) << setfill('0') << to_string(item.first.GetMonth()) << '-' << setw(2) << setfill('0') <<
                        to_string(item.first.GetDay()) << " " << it << endl;
            }
        }
    }
    return output;
}

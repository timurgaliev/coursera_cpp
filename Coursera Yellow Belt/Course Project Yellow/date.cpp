#include "date.h"
#include <sstream>
#include <iomanip>
#include <iostream>

Date::Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
}
int Date::GetYear() const {
    return year;
}
int Date::GetMonth() const {
    return month;
}
int Date::GetDay() const {
    return day;
}

bool operator<(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() * 12 * 31 + lhs.GetMonth() * 31 + lhs.GetDay() <
        rhs.GetYear() * 12 * 31 + rhs.GetMonth() * 31 + rhs.GetDay();
}
bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() * 12 * 31 + lhs.GetMonth() * 31 + lhs.GetDay() ==
        rhs.GetYear() * 12 * 31 + rhs.GetMonth() * 31 + rhs.GetDay();
}
bool operator>(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() * 12 * 31 + lhs.GetMonth() * 31 + lhs.GetDay() >
        rhs.GetYear() * 12 * 31 + rhs.GetMonth() * 31 + rhs.GetDay();
}
bool operator>=(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() * 12 * 31 + lhs.GetMonth() * 31 + lhs.GetDay() >=
        rhs.GetYear() * 12 * 31 + rhs.GetMonth() * 31 + rhs.GetDay();
}
bool operator<=(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() * 12 * 31 + lhs.GetMonth() * 31 + lhs.GetDay() <=
        rhs.GetYear() * 12 * 31 + rhs.GetMonth() * 31 + rhs.GetDay();
}
bool operator!=(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() * 12 * 31 + lhs.GetMonth() * 31 + lhs.GetDay() !=
        rhs.GetYear() * 12 * 31 + rhs.GetMonth() * 31 + rhs.GetDay();
}

ostream& operator<<(ostream& out, Date date) {
    out << fixed << setw(4) << setfill('0') << to_string(date.GetYear()) << '-' <<
            setw(2) << setfill('0') << to_string(date.GetMonth()) << '-' << setw(2) << setfill('0') <<
            to_string(date.GetDay());
    return out;
}

ostream& operator<<(ostream& out, pair<Date, string> data) {
    out << fixed << setw(4) << setfill('0') << to_string(data.first.GetYear()) << '-' <<
        setw(2) << setfill('0') << to_string(data.first.GetMonth()) << '-' << setw(2) << setfill('0') <<
        to_string(data.first.GetDay()) << " " << data.second;
    return out;
}


Date ParseDate(istream& stream) {
    string date;
    stream >> date;
    stringstream ss(date);
    int year;
    int month;
    int day;
    ss >> year;
    if (ss.peek() != '-') {
        throw invalid_argument("Wrong date format: " + date);
    }
    ss.ignore();
    if (ss.peek() == EOF) {
        throw invalid_argument("Wrong date format: " + date);
    }
    ss >> month;
    if (ss.peek() != '-') {
        throw invalid_argument("Wrong date format: " + date);
    }
    ss.ignore();
    if (ss.peek() == EOF) {
        throw invalid_argument("Wrong date format: " + date);
    }
    ss >> day;
    if (!ss.eof()) {
        throw invalid_argument("Wrong date format: " + date);
    }
    if (month > 12 || month < 1) {
        throw invalid_argument("Month value is invalid: " + to_string(month));
    }
    if (day > 31 || day < 1) {
        throw invalid_argument("Day value is invalid: " + to_string(day));
    }
    return Date({ year, month, day });
}


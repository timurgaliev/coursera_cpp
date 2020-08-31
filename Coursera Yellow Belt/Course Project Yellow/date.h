#pragma once
#include <string>
#include <iostream>

using namespace std;


class Date {
public:
	Date(int y, int m, int d);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	int year, month, day;
};

bool operator==(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& out, Date date);
ostream& operator<<(ostream& out, pair<Date, string> data);

Date ParseDate(istream& stream);



#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

#include "date.h"
#include "database.h"

using namespace std;

Date::Date(const int new_year, const int new_month, const int new_day) {
	year = new_year;
	month = new_month;
	day = new_day;
}

Date  ParseDate(istream& is) {
  int year, month, day;
  is >> year;
  is.ignore(1);
  is >> month;
  is.ignore(1);
  is >> day;
  Date date(year, month, day);
  return Date(year, month, day);
}

bool operator!=(const Date& date, const string str) {
	stringstream is;
	int year, month, day;

	is << str;
	is >> year;
	is.ignore(1);
	is >> month;
	is.ignore(1);
	is >>day;

	return (date.GetYear() != year || date.GetMonth() != month || date.GetDay() != day);
}

bool operator<(const Date& lhs, const Date& rhs) {
	auto p1 = make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay());
	auto p2 = make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
	return p1 < p2;
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return !(lhs < rhs);
}

bool operator==(const Date& lhs, const Date& rhs) {
	return (vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()}
	== vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()});
}

bool operator>(const Date& lhs, const Date& rhs) {
	return (!(lhs < rhs || lhs == rhs));
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return lhs < rhs || lhs == rhs;
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return lhs > rhs || lhs < rhs;
}

#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

class Date {
public:
	Date(const int new_year, const int new_month, const int new_day);

	int GetYear() const {return year;}

	int GetMonth() const {return month;};

	int GetDay() const {return day;};

private:
	int year;
	int month;
	int day;
};

Date  ParseDate(std::istream& is);

bool operator!=(const Date& date, const std::string str);

bool operator!=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

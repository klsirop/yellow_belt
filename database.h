#pragma once
#include <set>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "date.h"

std::ostream& operator<<(std::ostream& os, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);

class Database {
public:

	void Add(const Date&date, const std::string& event);

	void Print(std::ostream& os) const;

	template <class Func>
	int RemoveIf(Func func) {
		int count = 0;
		for (auto& ii : dbv) {
			auto it = stable_partition(begin(ii.second), end(ii.second),
			[func, ii](std::string m)
			{
				return func(ii.first, m);
			});
			count += it - ii.second.begin();
			ii.second.erase(ii.second.begin(), it);
		}
		for (auto it = db.begin(); it != db.end(); ) {
			for (auto i = it->second.begin(); i != it->second.end(); ) {
				auto next_i = next(i);
				if (func(it->first, *i))
					it->second.erase(*i);
				i = next_i;
				if (it->second.empty())
					break ;
			}
			auto next_it = next(it);
			if (it->second.size() == 0)
				db.erase(it->first);
			it = next_it;
			if (db.empty())
				break ;
		}
		return (count);
	}

	template <class Func>
	std::vector<std::string> FindIf(Func func) const {
		std::vector<std::string> vec;

		for (auto it : dbv) {
			for (auto i : it.second) {
				if (db.count(it.first) != 0 && db.at(it.first).count(i) != 0 && func(it.first, i)) {
					std::string str_date;
					std::stringstream ss;
					ss << it.first;
					ss >> str_date;
					vec.push_back(str_date + " " + i);
				}
			}
		}
		return vec;
	}

	std::string Last(const Date& date) const;

private:
	std::map<Date, std::set<std::string>> db;
	std::map<Date, std::vector<std::string>> dbv;
};





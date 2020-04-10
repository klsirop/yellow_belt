#include <map>
#include <utility>
#include <string>

#include "date.h"
#include "database.h"

using namespace std;

ostream& operator<<(ostream& os, const Date& date) {
	os << setw(4) << setfill('0') << date.GetYear() << "-" <<
		setw(2) << setfill('0') << date.GetMonth() << "-" <<
		setw(2) << setfill('0') << date.GetDay();

	return os;
}

void Database::Add(const Date&date, const string& event){
	if (db[date].count(event) == 0)
	{
		auto it = db.insert(pair<Date, set<string>>(date, set<string>{event}));
		if (!it.second) {
			db.at(date).insert(event);
		}

		auto it1 = dbv.insert(pair<Date, vector<string>>(date, vector<string>{event}));
		if (!it1.second) {
			dbv.at(date).push_back(event);
		}
	}
}

void Database::Print(ostream& os) const {
	for (auto it : dbv) {
		for (auto i : it.second) {
			if (db.count(it.first) != 0) {
				if (db.at(it.first).count(i) != 0)
					os << it.first << " " << i << endl;
			}
		}
	}
}

string Database::Last(const Date& date) const{
	if (db.empty()) {
		return "No entries";
	}

	auto low = db.lower_bound(date);

	auto res = low;
	if (low->first == date) {
		res = low;
	} else if (low == db.end()) {
		res = prev(low);
	} else if (low == db.begin() && low->first != date){
		return "No entries";
	} else {
		res = prev(low);
	}
	low = res;
	string low_set;
	if (dbv.count(low->first) != 0)
		low_set = dbv.at(low->first).back();

	auto low_date = low->first;
	stringstream s;
	string string_date;
	s << low_date;
	s >> string_date;
	return string_date + " " + low_set;
}

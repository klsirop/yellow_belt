#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include "condition_parser.h"
#include "node.h"
#include "database.h"

using namespace std;

ostream&  operator<<(ostream& os, const vector<string> v) {
  bool first = true;

  for (auto it : v) {
    if (!first)
        os << " ";
    else {
        first = false;
    }
    os << it;
  }
  os << endl;
  return os;
}

string ParseEvent(istream& is) {
  string event;

  getline(is, event);

  bool symb = false;
  for (unsigned int i = 0; i < event.size(); i++) {
    if (event[i] != ' ')
      symb = true;
    if (symb)
      break ;
    if (event[i] == ' ') {
      event.erase(i, 1);
      i--;
    }
  }
  return event;
}

using namespace std;

int main() {
  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

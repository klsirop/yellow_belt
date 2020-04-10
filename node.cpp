#include "node.h"

using namespace std;

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) {
	if (cmp_ == Comparison::Equal)
		return date_ == date;
	if (cmp_ == Comparison::NotEqual)
		return date_ != date;
	if (cmp_ == Comparison::Greater)
		return date_ < date;
	if (cmp_ == Comparison::GreaterOrEqual)
		return date_ <= date;
	if (cmp_ == Comparison::Less) {
		return date_ > date;
	}
	if (cmp_ == Comparison::LessOrEqual)
		return date_ >= date;
	else
		return 0;
};

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) {
	if (cmp_ == Comparison::Equal)
		return event_ == event;
	if (cmp_ == Comparison::NotEqual)
		return event_ != event;
	if (cmp_ == Comparison::Greater)
		return event_ < event;
	if (cmp_ == Comparison::GreaterOrEqual)
		return event_ <= event;
	if (cmp_ == Comparison::Less)
		return event_ > event;
	if (cmp_ == Comparison::LessOrEqual)
		return event_ >= event;
	else
		return 0;
};

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) {
	if (logical_operation_ == LogicalOperation::Or) {
		bool a1 = left_->Evaluate(date, event);
		bool a2 = root_->Evaluate(date, event);
		return a1 || a2;
	} else {
		bool a1 = left_->Evaluate(date, event);
		bool a2 = root_->Evaluate(date, event);
		return a1 && a2;
	}
};

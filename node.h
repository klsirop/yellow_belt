#pragma once
#include "date.h"
#include <memory>

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class 	LogicalOperation {
	Or,
	And,
};

class Node {
public:

	virtual bool Evaluate(const Date& date, const std::string& event) = 0;

};

class EmptyNode : public Node {
public:

	bool Evaluate(const Date& date, const std::string& event) override {
		return 1;
	};
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison cmp, const Date& date) : date_(date), cmp_(cmp) {}

	bool Evaluate(const Date& date, const std::string& event) override;

private:
	Date date_;
	Comparison cmp_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison cmp, const std::string& value) {
		cmp_ = cmp;
		event_ = value;
	}

	bool Evaluate(const Date& date, const std::string& event) override;

private:
	std::string event_;
	Comparison cmp_;
};

class LogicalOperationNode : public Node {
public:

	LogicalOperationNode(const LogicalOperation& logical_operation,
	std::shared_ptr<Node> left, std::shared_ptr<Node> root)
	: logical_operation_(logical_operation), left_(left), root_(root) {};

	bool Evaluate(const Date& date, const std::string& event) override;

private:
	LogicalOperation logical_operation_;
	std::shared_ptr<Node> left_;
	std::shared_ptr<Node> root_;
};

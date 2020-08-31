#pragma once
#include "date.h"
#include <memory>

using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class LogicalOperation {
	Or,
	And
};


class Node {
public:
	virtual bool Evaluate(const Date& date_, const string& event_) = 0;
};
class EmptyNode : public Node {
public:
	virtual bool Evaluate(const Date& date_, const string& event_) override;
};
class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& cmp, const Date& date_) :
		comparison(cmp), date(date_){}
	virtual bool Evaluate(const Date& date, const string& event) override;
private:
	const Comparison comparison;
	const Date date;
};
class EventComparisonNode : public Node{
public:
	EventComparisonNode(const Comparison& cmp, const string& _event_) :
		comparison(cmp), event(_event_){}
	virtual bool Evaluate(const Date& date_, const string& event_) override;
private:
	const Comparison comparison;
	const string event;
};
class LogicalOperationNode : public Node{
public:
	LogicalOperationNode(const LogicalOperation LO, const shared_ptr<Node> left_,
		const shared_ptr<Node> right_) : logical_operation(LO), left(left_), right(right_){}
	virtual bool Evaluate(const Date& date_, const string& event_) override;
private:
	const LogicalOperation logical_operation;
	shared_ptr<Node> left, right;
};
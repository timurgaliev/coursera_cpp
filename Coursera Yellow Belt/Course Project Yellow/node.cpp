#include "node.h"


bool EmptyNode::Evaluate(const Date& date_, const string& event_) {
	return true;
}

bool DateComparisonNode::Evaluate(const Date& date_, const string& event_) {
	switch (comparison) {
	case Comparison::Equal:
		return date_ == date;
	case Comparison::Greater:
		return date_ > date;
	case Comparison::GreaterOrEqual:
		return date_ >= date;
	case Comparison::Less:
		return date_ < date;
	case Comparison::LessOrEqual:
		return date_ <= date;
	case Comparison::NotEqual:
		return date_ != date;
	}
}

bool EventComparisonNode::Evaluate(const Date& date_, const string& event_) {
	switch (comparison) {
	case Comparison::Equal:
		return event_ == event;
	case Comparison::Greater:
		return event_ > event;
	case Comparison::GreaterOrEqual:
		return event_ >= event;
	case Comparison::Less:
		return event_ < event;
	case Comparison::LessOrEqual:
		return event_ <= event;
	case Comparison::NotEqual:
		return event_ != event;
	}
}

bool LogicalOperationNode::Evaluate(const Date& date_, const string& event_) {
	switch (logical_operation) {
	case LogicalOperation::Or:
		return left->Evaluate(date_, event_) || right->Evaluate(date_, event_);
	case LogicalOperation::And:
		return left->Evaluate(date_, event_) && right->Evaluate(date_, event_);
	}
}
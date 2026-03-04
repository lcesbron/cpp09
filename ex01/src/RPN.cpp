#include "RPN.hpp"
#include <cctype>
#include <stdexcept>

RPN::RPN(void) {};

void	RPN::pushChar(int c)
{
	t_value	toPush = {};

	switch (c)
	{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			toPush.type = VALUE;
			toPush.value = c - '0';
			break;
		case '+':
			toPush.type = ADD;
			break;
		case '-':
			toPush.type = SUB;
			break;
		case '*':
			toPush.type = MULT;
			break;
		case '/':
			toPush.type = DIV;
			break;
		default:
			throw std::invalid_argument("Error: Expected Char.");
	};
	this->expression_.push(toPush);
}

RPN::RPN(std::string const& expression)
{
	bool						expectChar = true;

	for(std::string::const_iterator	it = expression.begin(); it < expression.end(); it++)
	{
		if (expectChar)
		{
			this->pushChar(*it);
			expectChar = false;
		}
		else
		{
			if (!std::isspace(*it)) {throw std::invalid_argument("Error: Expected space.");}
			expectChar = true;
		}
	}
}

RPN::RPN(RPN const& toCopy):
expression_(toCopy.expression_) {}

RPN::~RPN(void) {};

RPN&	RPN::operator=(RPN const& toCopy)
{
	if (this != &toCopy)
	{
		this->expression_ = toCopy.expression_;
	}
	return (*this);
}

int		RPN::operation(t_type operatorType, std::pair<t_value, t_value> toOperate)
{
	switch (operatorType)
	{
		case ADD:
			return (toOperate.first.value + toOperate.second.value);
		case SUB:
			return (toOperate.first.value - toOperate.second.value);
		case MULT:
			return (toOperate.first.value * toOperate.second.value);
		case DIV:
			return (toOperate.first.value / toOperate.second.value);
		default :
			return (0);
	}
}

void	RPN::computeOperator(t_type operatorType)
{
	std::pair<t_value, t_value>	saved;
	t_value						toPush;

	this->expression_.pop();

	if (this->expression_.size() < 2) {throw std::invalid_argument("Expected values for operator");}

	this->computeRecursiveExpression();
	saved.first = this->expression_.top();
	this->expression_.pop();
	this->computeRecursiveExpression();
	saved.second = this->expression_.top();
	this->expression_.pop();

	toPush.type = VALUE;
	toPush.value = operation(operatorType, saved);
	this->expression_.push(toPush);
}

void	RPN::computeRecursiveExpression(void)
{
	switch (this->expression_.top().type)
	{
		case ADD: case SUB: case MULT: case DIV:
			computeOperator(this->expression_.top().type);
		default:
			break ;
	}
}

int		RPN::computeExpression(void)
{
	this->computeRecursiveExpression();
	if (this->expression_.size() > 1)
	{
		throw std::invalid_argument("Error");
	}
	return (this->expression_.top().value);
}

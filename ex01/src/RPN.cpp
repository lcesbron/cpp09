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

std::pair<t_value, t_value>	RPN::computeOperator(void)
{
	std::pair<t_value, t_value>	saved;

	this->expression_.pop();
	if (this->expression_.size() < 2) {throw std::invalid_argument("Expected values for operator");}
	this->computeExpression();
	saved.first = this->expression_.top();
	this->expression_.pop();
	this->computeExpression();
	saved.second = this->expression_.top();
	this->expression_.pop();
	return (saved);
}

void	RPN::computeAdd(void)
{
	std::pair<t_value, t_value>	toAdd = computeOperator();
	t_value						toPush;

	toPush.type = VALUE;
	toPush.value = toAdd.first.value + toAdd.first.value;
	this->expression_.push(toPush);
}

int		RPN::computeExpression(void)
{
	switch (this->expression_.top().type)
	{
		case ADD:
			computeAdd();
			break ;
		default:
			break ;
	}
	return (this->expression_.top().value);
}

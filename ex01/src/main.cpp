#include "RPN.hpp"
#include <exception>
#include <iostream>

int	main(int ac, char **av)
{
	RPN	rpn(av[1]);
	int	toPrint;

	if (ac != 2)
	{
		std::cout << "./RPN \"expression\"" << std::endl;
		return (1);
	}

	try
	{
		toPrint = rpn.computeExpression();
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}

	std::cout << toPrint << std::endl;
}

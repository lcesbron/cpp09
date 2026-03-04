#include "RPN.hpp"
#include <exception>
#include <iostream>
#include <ostream>

int	main(int ac, char **av)
{
	try
	{
		RPN	rpn(av[1]);
		int	toPrint;

		if (ac != 2)
		{
			std::cout << "./RPN \"expression\"" << std::endl;
			return (1);
		}

		toPrint = rpn.computeExpression();

		std::cout << toPrint << std::endl;
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
}

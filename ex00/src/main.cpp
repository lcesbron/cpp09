#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage: ./btc <input_file>" << std::endl;
		return (1);
	}

	BitcoinExchange	ex("assets/data.csv");

	try
	{
		ex.processInput(av[1]);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}

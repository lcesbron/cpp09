#include "BitcoinExchange.hpp"

int	main(int, char **av)
{
	BitcoinExchange	ex("assets/data.csv");
	ex.processInput(av[1]);
}

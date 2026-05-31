#include "PmergeMe.hpp"
#include <iostream>

int	main(void)
{
	std::vector<std::vector<uint32_t> > input;

	for (uint32_t i = 9; i; i--)
	{
		std::vector<uint32_t>	toInsert;
		toInsert.push_back(i);
		input.push_back(toInsert);
	}
	std::cout << "original : ";
	for (std::vector<std::vector<uint32_t> >::iterator it = input.begin(); it < input.end(); it++)
	{
		std::cout << it->front() << ' ';
	}
	std::cout << std::endl;
	PmergeMe::sort(input);

	for (std::vector<std::vector<uint32_t> >::iterator it = input.begin(); it < input.end(); it++)
	{
		std::cout << it->front() << ' ';
	}
}

#include "PmergeMe.hpp"
#include <iostream>

int	main(void)
{
	std::vector<uint64_t>	res;

	PmergeMe o("0 9 8 7 6 5 4 3 2 1");
	res = o.sort();
	for (int i = 0; i < 10; i++)
	{
		std::cout << res[i] << ' ';
	}
}

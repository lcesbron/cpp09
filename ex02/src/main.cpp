#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <sys/time.h>

static bool	parseValue(std::string const& token, uint32_t& out)
{
	if (token.empty())
	{
		return (false);
	}
	for (size_t i = 0; i < token.size(); i++)
	{
		if (token[i] < '0' || token[i] > '9')
		{
			return (false);
		}
	}

	std::istringstream	stream(token);
	unsigned long		value;

	stream >> value;
	if (stream.fail() || value > 4294967295UL)
	{
		return (false);
	}
	out = static_cast<uint32_t>(value);
	return (true);
}

static bool	parseArgs(int argc, char** argv, std::vector<uint32_t>& input)
{
	for (int i = 1; i < argc; i++)
	{
		uint32_t	value;

		if (!parseValue(argv[i], value))
		{
			return (false);
		}
		input.push_back(value);
	}
	return (!input.empty());
}

static double	elapsedMicroseconds(struct timeval const& start, struct timeval const& end)
{
	return ((end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec));
}

int	main(int argc, char** argv)
{
	std::vector<uint32_t>	input;

	if (!parseArgs(argc, argv, input))
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::cout << "Before:";
	for (size_t i = 0; i < input.size(); i++)
	{
		std::cout << ' ' << input[i];
	}
	std::cout << std::endl;

	struct timeval	start;
	struct timeval	end;

	std::vector<std::vector<uint32_t> >	vec;
	gettimeofday(&start, NULL);
	for (size_t i = 0; i < input.size(); i++)
	{
		vec.push_back(std::vector<uint32_t>(1, input[i]));
	}
	PmergeMe::sort(vec);
	gettimeofday(&end, NULL);
	double	vectorTime = elapsedMicroseconds(start, end);

	std::deque<std::deque<uint32_t> >	deq;
	gettimeofday(&start, NULL);
	for (size_t i = 0; i < input.size(); i++)
	{
		deq.push_back(std::deque<uint32_t>(1, input[i]));
	}
	PmergeMe::sort(deq);
	gettimeofday(&end, NULL);
	double	dequeTime = elapsedMicroseconds(start, end);

	std::cout << "After:";
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << ' ' << vec[i].front();
	}
	std::cout << std::endl;

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << input.size()
		<< " elements with std::vector : " << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << input.size()
		<< " elements with std::deque : " << dequeTime << " us" << std::endl;

	return (0);
}

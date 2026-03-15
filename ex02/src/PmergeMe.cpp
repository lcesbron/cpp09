#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void):
hasInput_(false),
elementSize_(1) {}

PmergeMe::PmergeMe(std::string const& toLoad):
hasInput_(true),
elementSize_(1)
{
	this->loadInput(toLoad);
}

PmergeMe::PmergeMe(std::vector<uint32_t> const& toLoad):
hasInput_(true),
elementSize_(1)
{
	this->loadInput(toLoad);
}

PmergeMe::~PmergeMe(void) {}



#include "PmergeMe.hpp"
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <vector>

PmergeMe::PmergeMe(void):
hasInput_(false),
elementSize_(1) {}

PmergeMe::PmergeMe(std::string const& toLoad):
elementSize_(1)
{
	this->loadInput(toLoad);
}

PmergeMe::PmergeMe(PmergeMe const& toCopy):
odd_(toCopy.odd_),
hasInput_(toCopy.hasInput_),
elementSize_(toCopy.elementSize_),
input_(toCopy.input_),
output_(toCopy.output_) {}

PmergeMe::PmergeMe(std::vector<uint64_t> const& toLoad, uint64_t elementSize):
elementSize_(elementSize)
{
	this->loadInput(toLoad);
}

PmergeMe::~PmergeMe(void) {}

PmergeMe&	PmergeMe::operator=(PmergeMe const& toAssign)
{
	if (this != &toAssign)
	{
		this->input_.clear();
		this->output_.clear();
		this->odd_ = toAssign.odd_;
		this->hasInput_ = toAssign.hasInput_;
		this->elementSize_ = toAssign.elementSize_;
		this->input_ = toAssign.input_;
		this->output_ = toAssign.output_;
	}
	return (*this);
}

void	PmergeMe::loadInput(std::string const& toLoad)
{
	char*	sptr = &toLoad[0];
	long long	current;

	while (sptr)
	{
		current = std::strtoll(sptr, &sptr, 10);
		if (current < 0)
		{
			throw std::invalid_argument("Negative value in input array");
		}
		if (static_cat<unsigned long long>(current) > ULONG_MAX)
		{
			throw std::invalid_argument("Overflow in input array");
		}
		this->input_.push_back(static_cast<uint64_t>(current));
	}
	this->odd_ = this->input_.size() % elementSize_;
	this->hasInput_ = true;
}

void	PmergeMe::loadInput(std::vector<uint64_t> const& toLoad)
{
	this->input_ = toLoad;
	this->odd_ = this->input_.size() % this->elementSize_;
	this->hasInput_ = true;
}

std::vector<uint64_t>	PmergeMe::sort(void)
{
	std::vector<uint64_t>	sortedMaxs;

	this->sortPairs();
	PmergeMe	recurse(this->input_, this->elementSize_ * 2);
	sortedMaxs = recurse.sort();
	this->updateIOVectors(sortedMaxs);
	// INSERT FIRST VALUE OF I IN BEGINNING OF O
	this->convertInputToInsertionOrder();
	this->insertElems();
	return (this->output_);
}

void	PmergeMe::sortPairs(void)
{
	for (std::vector<uint64_t>::iterator it = this->input_.begin(); it < this->input_.end(); it += elementSize_)
	{

	}
}

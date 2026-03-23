#include "PmergeMe.hpp"
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

PmergeMe::PmergeMe(void):
hasInput_(false) {}

PmergeMe::PmergeMe(std::string const& toLoad):
hasInput_(false)
{
	this->loadInput(toLoad);
}

PmergeMe::PmergeMe(PmergeMe const& toCopy):
odd_(toCopy.odd_),
hasInput_(toCopy.hasInput_),
input_(toCopy.input_),
inputPairs_(toCopy.inputPairs_),
output_(toCopy.output_) {}

PmergeMe::PmergeMe(std::vector<uint64_t> const& toLoad, uint64_t elementSize)
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

	if (this->hasInput_)
	{
		this->input_.clear();
		this->output_.clear();
		this->inputPairs_.clear();
	}
	while (sptr)
	{
		current = std::strtoll(sptr, &sptr, 10);
		if (current < 0)
		{
			throw std::invalid_argument("Negative value in input array");
		}
		if (static_cast<unsigned long long>(current) > ULONG_MAX)
		{
			throw std::invalid_argument("Overflow in input array");
		}
		this->input_.push_back(static_cast<uint64_t>(current));
	}
	this->odd_ = this->input_.size() % 2;
	this->hasInput_ = true;
}

void	PmergeMe::loadInput(std::vector<uint64_t> const& toLoad)
{
	if (this->hasInput_)
	{
		this->input_.clear();
		this->output_.clear();
		this->inputPairs_.clear();
	}
	this->input_ = toLoad;
	this->odd_ = this->input_.size() % 2;
	this->hasInput_ = true;
}

void	PmergeMe::loadPairs(void)
{
	std::pair<uint64_t, uint64_t>	current;
	std::vector<uint64_t>::iterator	it = this->input_.begin();
	std::vector<uint64_t>::iterator	last = this->input_.end() - 1;

	// Could also do one loop whith (while it + this->odd_ ...)
	// But would be less efficient
	if (this->odd_)
	{
		while (it + 1 != this->input_.end())
		{
			current.first = *it;
			current.second = it[1];
			this->inputPairs_.push_back(current);
			it += 2;
		}
		current.first = *it;
		this->inputPairs_.push_back(current);
	}
	else
	{
		while (it != this->input_.end())
		{
			current.first = *it;
			current.second = it[1];
			this->inputPairs_.push_back(current);
			it += 2;
		}
	}
}

void	PmergeMe::swapPairElems(std::pair<uint64_t,uint64_t>& p)
{
	if (p.first > p.second)
	{ 
		p.first ^= p.second;
		p.second ^= p.first;
		p.first ^= p.second;
	}
}

void	PmergeMe::sortPairs(void)
{
	std::vector<std::pair<uint64_t, uint64_t> >::iterator	it = this->inputPairs_.begin();
	std::vector<std::pair<uint64_t, uint64_t> >::iterator	last = this->inputPairs_.end() - 1;

	while (it < last)
	{
		swapPairElems(*it);
		++it;
	}
	if (!this->odd_)
	{
		swapPairElems(*it);
	}
}

std::vector<uint64_t>	PmergeMe::createMaxVector(void)
{
	std::vector<std::pair<uint64_t, uint64_t> >::iterator	it = this->inputPairs_.begin();
	std::vector<std::pair<uint64_t, uint64_t> >::iterator	last = this->inputPairs_.end() - 1;
	std::vector<uint64_t>									ret;

	while (it < last)
	{
		ret.push_back(it->second);
		++it;
	}
	if (!this->odd_)
	{
		ret.push_back(it->second);
	}
	return (ret);
}

std::vector<uint64_t>	PmergeMe::rearrangeMins(void)
{
	std::vector<uint64_t>									ret;
	std::vector<uint64_t>::iterator							maxIt;
	std::vector<std::pair<uint64_t, uint64_t> >::iterator	pairsIt;

	for (maxIt = this->output_.begin(); maxIt < this->output_.end(); maxIt++)
	{
		for (pairsIt = this->inputPairs_.begin(); pairsIt < this->inputPairs_.end() - this->odd_; pairsIt++)
		{
			if (*maxIt == pairsIt->second)
			{
				ret.push_back(pairsIt->first);
				this->inputPairs_.erase(pairsIt);
			}
		}
	}
	return (ret);
}

std::vector<uint64_t>	PmergeMe::createInsertionVector(void)
{
	std::vector<uint64_t>	ret;
	uint64_t		i = 0;
	uint64_t		counter;
	uint64_t		buf;
	uint64_t		prevGroupSize = 0;
	uint64_t		currentGroupSize = 2;

	while (ret.size() < this->input_.size())
	{
		counter = 0;
		while (ret.size() < this->input_.size() && counter < currentGroupSize)
		{
			ret.insert(ret.begin() + prevGroupSize, i);
			++i;
			++counter;
		}
		buf = currentGroupSize;
		currentGroupSize = 2 * prevGroupSize + currentGroupSize;
		prevGroupSize = buf;
	}
	return (ret);
}

//std::vector<uint64_t>	PmergeMe::createInsertionVector(void)
//{
//	std::vector<uint64_t>			ret;
//	uint64_t						counter;
//	uint64_t						buf;
//	uint64_t						prevGroupSize = 0;
//	uint64_t						currentGroupSize = 2;
//
//	while (this->input_.size())
//	{
//		counter = 0;
//		while (this->input_.size() && counter < currentGroupSize)
//		{
//			ret.insert(ret.begin() + prevGroupSize, *it);
//			this->input_.erase(this->input_.begin());
//			++counter;
//		}
//		buf = currentGroupSize;
//		currentGroupSize = 2 * prevGroupSize + currentGroupSize;
//		prevGroupSize = buf;
//	}
//	return (ret);
//}

void	PmergeMe::binaryInsert(void)
{
	
}

std::vector<uint64_t>	PmergeMe::sort(void)
{
	std::vector<uint64_t>	sortedMaxs;
	PmergeMe				recurse;

	if (!this->hasInput_)
		throw std::logic_error("Can't sort without input.");
	loadPairs();
	sortPairs();
	sortedMaxs = createMaxVector();
	recurse.loadInput(sortedMaxs);
	sortedMaxs = recurse.sort();
	this->output_ = sortedMaxs;
	this->input_ = rearrangeMins();
	this->input_ = createInsertionVector();
	binaryInsert();
	return (this->output_);
}

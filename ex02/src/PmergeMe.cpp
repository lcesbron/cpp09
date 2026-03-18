#include "PmergeMe.hpp"
#include <climits>
#include <cstdint>
#include <cstdlib>
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
	std::vector<uint64_t>::iterator							max_it;
	std::vector<std::pair<uint64_t, uint64_t> >::iterator	pairs_it;

	for (max_it = this->output_.begin(); max_it < this->output_.end(); max_it++)
	{
		for (pairs_it = this->inputPairs_.begin(); pairs_it < this->inputPairs_.end() - this->odd_; pairs_it++)
		{
			if (*max_it == pairs_it->second)
			{
				ret.push_back(pairs_it->first);
				this->inputPairs_.erase(pairs_it);
			}
		}
	}
	return (ret);
}

std::vector<uint64_t>	PmergeMe::createInsertionVector(void)
{
	std::vector<uint64_t>			ret;
	std::vector<uint64_t>::iterator	it;


	return (ret);
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
	insert();
	return (this->output_);
}




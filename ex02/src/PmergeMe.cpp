#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe(void) {}
PmergeMe::PmergeMe(PmergeMe const&) {}
PmergeMe&	PmergeMe::operator=(PmergeMe const&) {return (*this);}
PmergeMe::~PmergeMe(void) {}

std::vector<uint32_t>	PmergeMe::createInsertionVector(uint32_t nbElems)
{
  std::vector<uint32_t>	ret;
  uint32_t				i = 0;
  uint32_t				counter;
  uint32_t				buf;
  uint32_t				prevGroupSize = 0;
  uint32_t				currentGroupSize = 2;
  uint32_t				insertDelta = 0;

  while (ret.size() < nbElems)
  {
  	counter = 0;
  	while (ret.size() < nbElems && counter < currentGroupSize)
  	{
  		ret.insert(ret.begin() + insertDelta, i);
  		++i;
  		++counter;
  	}
  	buf = currentGroupSize;
  	currentGroupSize = 2 * prevGroupSize + currentGroupSize;
  	prevGroupSize = buf;
  	insertDelta += prevGroupSize;
  }
  return (ret);
}

void	PmergeMe::sort(std::vector<std::vector<uint32_t> >& toSort)
{
	if (toSort.size() <= 1)
	{
		return ;
	}

	bool				hasLeftOver = toSort.size() % 2;
	std::vector<uint32_t>	leftOver;

	if (hasLeftOver)
	{
		leftOver = toSort.back();
		toSort.pop_back();
	}

	for (std::vector<std::vector<uint32_t> >::iterator it = toSort.begin(); it < toSort.end(); it++)
	{
		if (comp(*it, *(it + 1)))
		{
			it->insert(it->begin(), (it + 1)->begin(), (it + 1)->end());
		}
		else
		{
			it->insert(it->end(), (it + 1)->begin(), (it + 1)->end());
		}
		toSort.erase(it + 1);
	}

	sort(toSort);

	std::vector<std::vector<uint32_t> >	toInsert;
	uint32_t							pairSize = toSort.front().size() / 2;

	for (std::vector<std::vector<uint32_t> >::iterator it = toSort.begin(); it < toSort.end(); it++)
	{
		std::vector<uint32_t>	buf(it->begin() + pairSize, it->end());
		toInsert.push_back(buf);
		it->erase(it->begin() + pairSize, it->end());
	}
	if (hasLeftOver)
	{
		toInsert.push_back(leftOver);
	}

	toSort.insert(toSort.begin(), toInsert.front());
	toInsert.erase(toInsert.begin());

	std::vector<uint32_t> insertionVector = createInsertionVector(toInsert.size());
	for (uint32_t i = 0; i < insertionVector.size(); i++)
	{
		std::vector<std::vector<uint32_t> >::iterator index = std::upper_bound(toSort.begin(), toSort.begin() + i + 2 + insertionVector[i], toInsert[insertionVector[i]], comp<std::vector<uint32_t> >);
		toSort.insert(index, toInsert[insertionVector[i]]);
	}
}

void	PmergeMe::sort(std::deque<std::deque<uint32_t> >& toSort)
{
	if (toSort.size() <= 1)
	{
		return ;
	}

	bool				hasLeftOver = toSort.size() % 2;
	std::deque<uint32_t>	leftOver;

	if (hasLeftOver)
	{
		leftOver = toSort.back();
		toSort.pop_back();
	}

	for (size_t i = 0; i + 1 < toSort.size(); i++)
	{
		if (comp(toSort[i], toSort[i + 1]))
		{
			toSort[i].insert(toSort[i].begin(), toSort[i + 1].begin(), toSort[i + 1].end());
		}
		else
		{
			toSort[i].insert(toSort[i].end(), toSort[i + 1].begin(), toSort[i + 1].end());
		}
		toSort.erase(toSort.begin() + i + 1);
	}

	sort(toSort);

	std::deque<std::deque<uint32_t> >	toInsert;
	uint32_t							pairSize = toSort.front().size() / 2;

	for (size_t i = 0; i < toSort.size(); i++)
	{
		std::deque<uint32_t>	buf(toSort[i].begin() + pairSize, toSort[i].end());
		toInsert.push_back(buf);
		toSort[i].erase(toSort[i].begin() + pairSize, toSort[i].end());
	}
	if (hasLeftOver)
	{
		toInsert.push_back(leftOver);
	}

	toSort.insert(toSort.begin(), toInsert.front());
	toInsert.erase(toInsert.begin());

	std::vector<uint32_t> insertionVector = createInsertionVector(toInsert.size());
	for (uint32_t i = 0; i < insertionVector.size(); i++)
	{
		std::deque<std::deque<uint32_t> >::iterator index = std::upper_bound(toSort.begin(), toSort.begin() + i + 2 + insertionVector[i], toInsert[insertionVector[i]], comp<std::deque<uint32_t> >);
		toSort.insert(index, toInsert[insertionVector[i]]);
	}
}

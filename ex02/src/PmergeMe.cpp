#include "PmergeMe.hpp"
#include <algorithm>

PmergeMe::PmergeMe(void) {}

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

bool						PmergeMe::comp(std::vector<uint32_t> const& a, std::vector<uint32_t> const& b)
{
	return (a.front() < b.front());
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
		std::vector<std::vector<uint32_t> >::iterator index = std::upper_bound(toSort.begin(), toSort.begin() + i + 2 + insertionVector[i], toInsert[insertionVector[i]], comp);
		toSort.insert(index, toInsert[insertionVector[i]]);
	}
}

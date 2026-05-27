#include "PmergeMe.hpp"
#include <cstdint>

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

	for (std::vector<std::vector<uint32_t> >::iterator it = toSort.begin(); it < toSort.end(); it += 2)
	{
		it->insert(it->end(), (it + 1)->begin(), (it + 1)->end());
		toSort.erase(it + 1);
	}

	for (std::vector<std::vector<uint32_t> >::iterator it = toSort.begin(); it < toSort.end(); it += 1)
	{
		if (it->front() < *(it->begin() + it->size() / 2))
		{
			std::vector<uint32_t>	buf(it->begin() + it->size() / 2, it->end());
			it->erase(it->begin() + it->size() / 2, it->end());
			it->insert(it->begin(), buf.begin(), buf.end());
		}
	}

	sort(toSort);

	std::vector<std::vector<uint32_t> >	toInsert;
	uint32_t							pairSize = toSort.front().size() / 2;

	for (std::vector<std::vector<uint32_t> >::iterator it; it < toSort.end(); it++)
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


}

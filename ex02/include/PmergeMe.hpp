#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <cstdint>
#include <utility>
# include <vector>
# include <string>
# include <stdint.h>

class PmergeMe
{
	private:
		bool										odd_;
		bool										hasInput_;
		std::vector<uint64_t>						input_;
		std::vector<std::pair<uint64_t, uint64_t>>	inputPairs_;
		std::vector<uint64_t>						output_;

		PmergeMe(PmergeMe const& toCopy);
		PmergeMe&	operator=(PmergeMe const& toAssign);

		PmergeMe(std::vector<uint64_t> const& toLoad, uint64_t elementSize);
		void	loadInput(std::vector<uint64_t> const& toLoad);

		void					loadPairs(void);
		void					sortPairs(void);
		std::vector<uint64_t>	createMaxVector(void);
		std::vector<uint64_t>	rearrangeMins(void);
		std::vector<uint64_t>	createInsertionVector(void);
		void					binaryInsert(void);

		void					PmergeMe::swapPairElems(std::pair<uint64_t,uint64_t>& p);
	public:
		PmergeMe(void);
		PmergeMe(std::string const& toLoad);
		~PmergeMe(void);

		void	loadInput(std::string const& toLoad);

		std::vector<uint64_t>	sort(void);
};

#endif //PMERGEME_HPP

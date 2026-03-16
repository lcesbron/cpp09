#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <cstdint>
# include <vector>
# include <string>
# include <stdint.h>

class PmergeMe
{
	private:
		bool										odd_;
		bool										hasInput_;
		uint32_t									elementSize_;
		std::vector<uint64_t>						input_;
		std::vector<uint64_t>						output_;

		PmergeMe(PmergeMe const& toCopy);
		PmergeMe&	operator=(PmergeMe const& toAssign);

		PmergeMe(std::vector<uint64_t> const& toLoad, uint64_t elementSize);
		void	loadInput(std::vector<uint64_t> const& toLoad);

		void	sortPairs(void);
		void	updateIOVectors(std::vector<uint64_t> const& sortedMaxs);
		void	convertInputToInsertionOrder(void);
		void	insertElems(void); // Binary Search

		void	swapValues(uint64_t& index1, uint64_t& index2);
	public:
		PmergeMe(void);
		PmergeMe(std::string const& toLoad);
		~PmergeMe(void);

		void	loadInput(std::string const& toLoad);

		std::vector<uint64_t>	sort(void);
};

#endif //PMERGEME_HPP

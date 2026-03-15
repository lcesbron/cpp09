#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <string>
#include <stdint.h>

class PmergeMe
{
	private:
		bool										odd_;
		bool										hasInput_;
		uint32_t									elementSize_;
		std::vector<uint32_t>						input_;
		std::vector<uint32_t>						output_;

		PmergeMe(PmergeMe const& toCopy);
		PmergeMe&	operator=(PmergeMe const& toCopy);

		PemergeMe(std::vector<uint32_t> const& toLoad, uint32_t elementSize);

		void					sortPairs(void);


	public:
		PmergeMe(void);
		PmergeMe(std::string const& toLoad);
		PmergeMe(std::vector<uint32_t> const& toLoad);
		~PmergeMe(void);


		void	loadInput(std::string const& toLoad);
		void	loadInput(std::vector<uint32_t> const& toLoad);

		std::vector<uint32_t>	sort(void);
};

#endif //PMERGEME_HPP

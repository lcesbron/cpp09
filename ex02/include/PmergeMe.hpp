#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <string>
# include <utility>
# include <cstdint>

class PmergeMe
{
	private:
		bool										odd;
		bool										hasInput;
		std::vector<uint32_t>						input;
		std::vector<uint32_t>						output;

		PmergeMe(std::vector<uint32_t> const& toLoad, uint32_t pairSize);

		void					sortRecursive(uint32_t elementSize);

		void					fillPairs(void);
		void					orderPairsElems(void);
		void					sortPairs(void); // Here is recursive
		void					insertMaxs(void);
		void					insertMins(void); // Here is tricky part (pseudo Jacobsthen)

	public:
		PmergeMe(void);
		PmergeMe(std::string const& toLoad);
		PmergeMe(std::vector<uint32_t> const& toLoad);
		PmergeMe(PmergeMe const& toCopy);
		~PmergeMe(void);

		PmergeMe&	operator=(PmergeMe const& toCopy);

		void	loadInput(std::string const& toLoad);
		void	loadInput(std::vector<uint32_t> const& toLoad);

		void	sort(void);
};

#endif //PMERGEME_HPP

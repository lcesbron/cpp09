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
		std::vector<uint32_t>						input;
		std::vector<std::pair<uint32_t, uint32_t>>	pairs;
		std::vector<uint32_t>						output;

		void					fillPairs(void);
		void					orderPairsElems(void);
		void					sortPairs(void); // Here is recursive
		void					insertMaxs(void);
		void					insertMins(void); // Here is tricky part (pseudo Jacobsthen)

		std::vector<uint32_t>	makeVectorFromPairsMax(void) const;

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

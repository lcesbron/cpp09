#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <stdint.h>

class PmergeMe
{
	private:
		static std::vector<uint32_t>	createInsertionVector(uint32_t nbElems);
		static bool						comp(std::vector<uint32_t> const& a, std::vector<uint32_t> const& b);
	public:
		PmergeMe(void);

		static void	sort(std::vector<std::vector<uint32_t> >& toSort);
};

#endif //PMERGEME_HPP

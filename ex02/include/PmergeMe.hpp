#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <cstdint>
# include <stdint.h>


class PmergeMe
{
	private:
		static createInsertionVector(uint32_t nbElems);
	public:
		void	sort(std::vector<std::vector<uint32_t> >& toSort);
};

#endif //PMERGEME_HPP

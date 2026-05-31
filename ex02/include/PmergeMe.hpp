#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <stdint.h>

class PmergeMe
{
	private:
		static std::vector<uint32_t>	createInsertionVector(uint32_t nbElems);

		template <typename T>
		static bool	comp(T const& a, T const& b)
		{
			return (a.front() < b.front());
		}
	public:
		PmergeMe(void);
		PmergeMe(PmergeMe const& toCopy);
		PmergeMe&	operator=(PmergeMe const& toCopy);
		~PmergeMe(void);

		static void	sort(std::vector<std::vector<uint32_t> >& toSort);
		static void	sort(std::deque<std::deque<uint32_t> >& toSort);
};

#endif //PMERGEME_HPP

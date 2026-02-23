#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <ctime>
# include <string>

typedef struct s_timeValuePair	t_timeValuePair;

struct s_timeValuePair
{
	std::tm time;
	float	value;
}

class BitcoinExchange
{
	private:
		std::map<std::tm, float>	priceHistory_;

		BitcoinExchange(void);

		void						addLine(std::string line);
		static t_timeValuePair		parseLine(std::string line);
	public:
		BitcoinExchange(std::string priceHistoryCSVFile);
		BitcoinExchange(BitcoinExchange const& toCopy);
		~BitcoinExchange(void);

		BitcoinExchange&	operator=(BitcoinExchange const& toCopy);
};

#endif //BITCOINEXCHANGE_HPP

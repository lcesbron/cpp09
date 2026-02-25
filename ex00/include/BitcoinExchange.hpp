#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <ctime>
# include <string>
#include <utility>

class BitcoinExchange
{
	private:
		std::map<std::time_t, float>	priceHistory_;

		BitcoinExchange(void);

		void									addLine(std::pair<std::time_t, double> pair);
		static std::pair<std::time_t, double>	parseLine(std::string line);
	public:
		BitcoinExchange(std::string priceHistoryCSVFile);
		BitcoinExchange(BitcoinExchange const& toCopy);
		~BitcoinExchange(void);

		BitcoinExchange&	operator=(BitcoinExchange const& toCopy);
};

#endif //BITCOINEXCHANGE_HPP

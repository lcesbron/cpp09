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

		static bool								isCSVLineValid(std::string line);

		static bool								isDateValid(std::string line);
		static bool								isDatePossible(unsigned int day, unsigned int mounth, unsigned int year);
		static bool								isLeapYear(unsigned int year);

		static bool								isValueValid(std::string value);

		static std::pair<std::time_t, double>	parseLine(std::string line);
	public:
		BitcoinExchange(std::string priceHistoryCSVFile);
		BitcoinExchange(BitcoinExchange const& toCopy);
		~BitcoinExchange(void);

		BitcoinExchange&	operator=(BitcoinExchange const& toCopy);
};

#endif //BITCOINEXCHANGE_HPP

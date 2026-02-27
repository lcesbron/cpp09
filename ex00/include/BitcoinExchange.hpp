#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <ctime>
# include <string>
#include <utility>

class BitcoinExchange
{
	private:
		std::map<std::time_t, double>	priceHistory_;

		BitcoinExchange(void);

		static bool								isDateValid(std::string line);
		static bool								isDatePossible(unsigned int day, unsigned int mounth, unsigned int year);
		static bool								isLeapYear(unsigned int year);
		static bool								isValueValid(std::string value);


		static bool								isCSVLineValid(std::string line);
		static std::pair<std::time_t, double>	parseCSVLine(std::string line);

		static size_t							isInputLineValid(std::string line);
		static std::pair<std::time_t, double>	parseInputLine(std::string line);
		std::pair<std::time_t, double>			findClosestValue(std::pair<std::time_t, double> toFind) const;
		std::pair<std::time_t, double>			computeFinalValue(std::pair<std::time_t, double>) const;
	public:
		BitcoinExchange(std::string priceHistoryCSVFile);
		BitcoinExchange(BitcoinExchange const& toCopy);
		~BitcoinExchange(void);

		BitcoinExchange&	operator=(BitcoinExchange const& toCopy);

		void				processInput(std::string inputFileName) const;
};

#endif //BITCOINEXCHANGE_HPP

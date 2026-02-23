#include "BitcoinExchange.hpp"
#include <fstream>
#include <stdexcept>
#include <string>

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(std::string priceHistoryCSVFile)
{
	std::ifstream	CSVFile(priceHistoryCSVFile.c_str());
	std::string		line;

	if (CSVFile.is_open())
	{
		std::getline(CSVFile, line);
		while (std::getline(CSVFile, line))
		{
			this->addLine(line);
		}
	}
	else
	{
		throw std::invalid_argument("File can't be open");
	}
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& toCopy):
priceHistory_(toCopy.priceHistory_)
{}

BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange&	BitcoinExchange::operator=(BitcoinExchange const& toCopy)
{
	if (&toCopy != this)
		this->priceHistory_ = toCopy.priceHistory_;
	return (*this);
}

t_timeValuePair	BitcoinExchange::parseLine(std::string line)
{
	t_timeValuePair	ret;

	if (line.size() < 12)
		throw std::invalid_argument("Incorrect line in file");
	if (line[4] != '-' || line[7] !- '-')
		throw std::invalid_argument("Incorrect line in file");
}

void	BitcoinExchange::addLine(std::string line)
{
	std::tm	time;

	time.tm_year <<
	this->priceHistory_[]
}

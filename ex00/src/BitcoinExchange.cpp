#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(std::string priceHistoryCSVFile)
{
	std::ifstream	CSVFile(priceHistoryCSVFile.c_str());
	std::string		line;

	if (CSVFile.is_open())
	{
		std::getline(CSVFile, line);
		char							*buf = new char[11];
		while (std::getline(CSVFile, line))
		{
			std::pair<std::time_t, double>	tmp = this->parseLine(line);
			std::tm*						time_tm = localtime(&tmp.first);

			std::strftime(buf, 11, "%Y-%m-%d", time_tm);
			std::cout << buf << std::endl;
			std::cout << tmp.second << std::endl;
			this->addLine(tmp);
		}
		delete [] buf;
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

std::pair<std::time_t, double>	BitcoinExchange::parseLine(std::string line)
{
	std::tm							time;
	std::pair<std::time_t, double>	ret;

	if (line.size() < 12 || line[4] != '-' || line[7] != '-')
		throw std::invalid_argument("Incorrect line in file");
	for (std::string::iterator i = line.begin(); i < line.begin() + 4 ; i++)
		if (!std::isdigit(*i)) {throw std::invalid_argument("Incorrect line in file");}
	for (std::string::iterator i = line.begin() + 5; i < line.begin() + 7 ; i++)
		if (!std::isdigit(*i)) {throw std::invalid_argument("Incorrect line in file");}
	for (std::string::iterator i = line.begin() + 8; i < line.begin() + 10 ; i++)
		if (!std::isdigit(*i)) {throw std::invalid_argument("Incorrect line in file");}
	time.tm_year = std::atoi(&*line.begin());
	if ((time.tm_mon = std::atoi(&*(line.begin() + 5)) - 1) > 11) {throw std::invalid_argument("Incorrect line in file");}
	if ((time.tm_mday = std::atoi(&*(line.begin() + 8))) > 31) {throw std::invalid_argument("Incorrect line in file");}
	if ((ret.second = std::atof(&*(line.begin() + 11))) > 1000.0) {throw std::invalid_argument("Incorrect line in file");}
	ret.first = std::mktime(&time);
	return (ret);
}

void	BitcoinExchange::addLine(std::pair<std::time_t, double> pair)
{
	this->priceHistory_.insert(pair);
}

#include "BitcoinExchange.hpp"
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <exception>
#include <fstream>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>

BitcoinExchange::BitcoinExchange(void) {}

BitcoinExchange::BitcoinExchange(std::string priceHistoryCSVFile)
{
	std::ifstream					CSVFile(priceHistoryCSVFile.c_str());
	std::string						line;
	std::pair<std::time_t, double>	currentPair;

	if (CSVFile.is_open())
	{
		std::getline(CSVFile, line);
		while (std::getline(CSVFile, line))
		{
			try
			{
				currentPair = this->parseCSVLine(line);
			}
			catch (std::exception& e)
			{
				std::cout << line << "->" << e.what() << std::endl;
			}
			this->priceHistory_.insert(currentPair);
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

bool	BitcoinExchange::isCSVLineValid(std::string line)
{
	if (line.size() < 12 || line.find(',', 0) != 10)
		return (false);
	return (true);
}

bool	BitcoinExchange::isValueValid(std::string value)
{
	bool					gotComma = false;
	std::string::iterator	i = value.begin();

	while (i < value.end())
	{
		if (!std::isdigit(*i) && !(*i == '.' && !gotComma && i != value.end() - 1)) {return (false);}
		if (*i == '.')
			gotComma = true;
		++i;
	}
	return (true);
}

bool	BitcoinExchange::isLeapYear(unsigned int year)
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

bool	BitcoinExchange::isDatePossible(unsigned int day, unsigned int mounth, unsigned int year)
{
	switch (mounth)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return (day <= 31 ? true : false);
		case 2:
			return (day <= 28 + BitcoinExchange::isLeapYear(year) ? true : false);
		case 4: case 6: case 9: case 11:
			return (day <= 30 ? true : false);
		default:
			return (false);
	}
}

bool	BitcoinExchange::isDateValid(std::string date)
{
	std::string::iterator	i = date.begin();
	unsigned int			year = 0;
	unsigned int			mounth = 0;
	unsigned int			day = 0;

	if (date[4] != '-' || date[7] != '-')
		return (false);
	while (i < date.begin() + 4)
	{
		if (!std::isdigit(*i)) {return (false);}
		year = *i - '0' + year * 10;
		++i;
	}
	if (*i++ != '-') {return (false);}
	while (i < date.begin() + 7)
	{
		if (!std::isdigit(*i)) {return (false);}
		mounth = *i - '0' + mounth * 10;
		++i;
	}
	if (*i++ != '-') {return (false);}
	while (i < date.end())
	{
		if (!std::isdigit(*i)) {return (false);}
		day = *i - '0' + day * 10;
		++i;
	}
	return (isDatePossible(day, mounth, year));
}

std::pair<std::time_t, double>	BitcoinExchange::parseCSVLine(std::string line)
{
	std::tm							time = {};
	std::pair<std::time_t, double>	ret;
	std::string						date;
	std::string						value;

	if (!BitcoinExchange::isCSVLineValid(line))
		throw std::invalid_argument("Incorrect line format in .csv file.");
	date = line.substr(0, 10);
	if (!BitcoinExchange::isDateValid(date))
		throw std::invalid_argument("Incorrect date in .csv file.");
	value = line.substr(11, line.size() - 11);
	if (!BitcoinExchange::isValueValid(value))
		throw std::invalid_argument("Incorrect value in .csv file.");
	strptime(date.c_str(), "%Y-%m-%d", &time);
	ret.first = std::mktime(&time);
	ret.second = std::atof(value.c_str());
	return (ret);
}

size_t	BitcoinExchange::isInputLineValid(std::string line)
{
	size_t	ret = line.find("|");

	if (line.size() < 12 || ret == std::string::npos)
		return (0);
	return (ret);
}

std::pair<std::time_t, double>	BitcoinExchange::parseInputLine(std::string line)
{
	std::pair<std::time_t, double>	ret;
	std::string						date;
	std::string						value;
	std::tm							tp;
	size_t							pipeLocation = isInputLineValid(line);

	if (!pipeLocation)
		throw std::invalid_argument("Invalid input line.");
	date = line.substr(0, 10);
	if (!BitcoinExchange::isDateValid(date))
		throw std::invalid_argument("Incorrect date in input file.");
	while (pipeLocation++ < line.size() && std::isspace(line[pipeLocation]));
	if (pipeLocation == line.size())
		throw std::invalid_argument("Invalid input line.");
	value = line.substr(pipeLocation, line.size() - pipeLocation);
	if (!BitcoinExchange::isValueValid(value))
		throw std::invalid_argument("Incorrect value in input file.");
	strptime(date.c_str(), "%Y-%m-%d", &tp);
	ret.first = std::mktime(&tp);
	ret.second = std::atof(value.c_str());
	if (ret.second > 1000)
		throw std::invalid_argument("Value over 1000 in input line.");
	return (ret);
}

std::pair<std::time_t, double>	BitcoinExchange::computeFinalValue(std::pair<std::time_t, double> toFind) const
{
	std::map<std::time_t, double>::const_iterator	it = this->priceHistory_.lower_bound(toFind.first);

	if (toFind.first == it->first)
		return (*it);
	else if (it == this->priceHistory_.begin())
	{
		throw std::invalid_argument("No date correponding in database.");
	}
	else
	{
		return (*(it--));
	}
}

void	printLineValue(std::pair<std::time_t, double> currentLine, std::pair<std::time_t, double> finalValue)
{
	char buf[11];

	strftime(buf, 11, "%Y-%m-%d", std::localtime(&finalValue.first));
	std::cout << buf << " => " << currentLine.second << " = " << currentLine.second * finalValue.second <<std::endl;
}

void	BitcoinExchange::processInput(std::string inputFileName) const
{
	std::ifstream					inputFile(inputFileName.c_str());
	std::string						line;
	std::pair<std::time_t, double>	currentLine;
	std::pair<std::time_t, double>	finalValue;

	if (!inputFile.is_open())
	{
		throw std::invalid_argument("File can't be open");
	}
	std::getline(inputFile, line);
	while (std::getline(inputFile, line))
	{
		try
		{
			currentLine = this->parseInputLine(line);
			finalValue = this->computeFinalValue(currentLine);
			printLineValue(currentLine, finalValue);
		}
		catch (std::exception& e)
		{
			std::cout << "error: " << e.what() << " line: " << line << std::endl;
		}
	}
	}

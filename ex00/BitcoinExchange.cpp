/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:46:36 by lcournoy          #+#    #+#             */
/*   Updated: 2025/12/17 16:46:36 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _db(other._db) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        _db = other._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open database file.");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date;
        double value;
        if (std::getline(ss, date, ',') && ss >> value)
            _db[date] = value;
    }
    file.close();

}

bool check_date(const std::string &date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    return true;
}


double BitcoinExchange::find_date(const std::string &date)
{
    std::map<std::string, double>::iterator it;

    it = _db.lower_bound(date);

    if (it == _db.begin() && it->first != date)
        throw std::runtime_error("Error: no earlier date available.");
    if (it == _db.end() || it->first != date)
        --it;

    return it->second;
}

void BitcoinExchange::processInput(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date;
        double value;
        if (!(std::getline(ss, date, '|') && ss >> value))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        while (!date.empty() && date[date.size() - 1] == ' ')
            date.erase(date.size() - 1);
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        if (!check_date(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        try
        {
            double rate = find_date(date);
            std::cout << date << " => " << value
                      << " = " << value * rate << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

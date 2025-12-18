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

void BitcoinExchange::processInput(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open input file.");
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date;
        double value;
        if (std::getline(ss, date, '|') && ss >> value)
        {
            if (date.empty() || value < 0)
                std::cout << "Error: Invalid input." << std::endl;
            else
            {
                auto it = _db.lower_bound(date);
                if (it != _db.end())
                    std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
                else
                    std::cout << "Error: No data available for the given date." << std::endl;
            }
        }
    }
    file.close();
}
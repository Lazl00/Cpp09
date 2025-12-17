/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:46:38 by lcournoy          #+#    #+#             */
/*   Updated: 2025/12/17 16:46:38 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, double> _db;

    public:
        BitcoinExchange();
        ~BitcoinExchange();

        void loadDatabase(const std::string &filename);
        void processInput(const std::string &filename);
};
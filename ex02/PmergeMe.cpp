/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:47:07 by lcournoy          #+#    #+#             */
/*   Updated: 2025/12/18 01:47:07 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vector(other._vector), _deque(other._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

bool    PmergeMe::check_doubles()
{
    int n = _vector.size();
      
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(_vector[i] == _vector[j])
                return true; 
        }
    }
    return false;
}

bool    check_entry(char *entry)
{
    unsigned    int value;

    for (int i = 0; entry[i]; i++)
    {
        if (!isdigit(entry[i]))
            throw std::runtime_error("Non-digit char detected.");
        if (i > 9)
            throw std::runtime_error("Values must fit in an int.");
    }
    value = atol(entry);
    if (value > INT32_MAX)
        throw std::runtime_error("Values must fit in an int.");
    return (1);
}

void PmergeMe::parsing(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        if (check_entry(av[i]))
        {
            _vector.push_back(atoi(av[i]));
            _deque.push_back(atoi(av[i]));
        }
        else
            throw std::runtime_error("Bad entry.");
    }
    if (check_doubles())
        throw std::runtime_error("Duplicate values found.");
}

void PmergeMe::sort_vector()
{
    std::vector<int> mins;
    std::vector<int> maxs;

    if (_vector.size() <= 1)
        return;

    for (int i = 0; i + 1 < _vector.size(); i += 2)
    {
        if (_vector[i] < _vector[i + 1])
        {
            mins.push_back(_vector[i]);
            maxs.push_back(_vector[i + 1]);
        }
        else
        {
            mins.push_back(_vector[i + 1]);
            maxs.push_back(_vector[i]);
        }
    }
    if (_vector.size() % 2 == 1)
        maxs.push_back(_vector.back());

    std::vector<int> sorted;
    sorted.push_back(maxs[0]);

    for (int i = 1; i < maxs.size(); i++)
    {
        int j = 0;
        while (j < sorted.size() && maxs[i] > sorted[j])
            j++;
        sorted.insert(sorted.begin() + j, maxs[i]);
    }
    for (int i = 0; i < mins.size(); i++)
    {
        int j = 0;
        while (j < sorted.size() && mins[i] > sorted[j])
            j++;
        sorted.insert(sorted.begin() + j, mins[i]);
    }

    _vector = sorted;
}

void PmergeMe::sort_deque()
{
    std::deque<int> mins;
    std::deque<int> maxs;

    if (_deque.size() <= 1)
        return;

    for (int i = 0; i + 1 < _deque.size(); i += 2)
    {
        if (_deque[i] < _deque[i + 1])
        {
            mins.push_back(_deque[i]);
            maxs.push_back(_deque[i + 1]);
        }
        else
        {
            mins.push_back(_deque[i + 1]);
            maxs.push_back(_deque[i]);
        }
    }
    if (_deque.size() % 2 == 1)
        maxs.push_back(_deque.back());

    std::deque<int> sorted;
    sorted.push_back(maxs[0]);

    for (int i = 1; i < maxs.size(); i++)
    {
        int j = 0;
        while (j < sorted.size() && maxs[i] > sorted[j])
            j++;
        sorted.insert(sorted.begin() + j, maxs[i]);
    }
    for (int i = 0; i < mins.size(); i++)
    {
        int j = 0;
        while (j < sorted.size() && mins[i] > sorted[j])
            j++;
        sorted.insert(sorted.begin() + j, mins[i]);
    }

    _deque = sorted;
}

void PmergeMe::display_before() const
{
    std::cout << "Before : " ;
    for (int i = 0; i < _vector.size(); i++)
        std::cout << _vector[i] << " " ;
    std::cout << std::endl;
}

void PmergeMe::display_after() const
{
    std::cout << "After : " ;
    for (int i = 0; i < _vector.size(); i++)
        std::cout << _vector[i] << " " ;
    std::cout << std::endl;
}


void PmergeMe::display_Vector() const
{
    std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : " << std::endl; // a voir comment afficher le temps (probablment avec une globale)
}
void PmergeMe::display_Deque() const
{
    std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : " << std::endl; // a voir comment afficher le temps // oui ca sert a rien mais je bloque sur des trucs betes.
}
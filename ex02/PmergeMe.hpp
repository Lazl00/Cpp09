/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:47:09 by lcournoy          #+#    #+#             */
/*   Updated: 2025/12/18 01:47:09 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <vector>
# include <deque>
# include <algorithm>
# include <chrono>
# include <stdexcept>
# include <limits>


class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int>  _deque;
    
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        bool check_doubles();
        void parsing(int ac, char **av);
        void sort_vector();
        void sort_deque();
        void display_before() const;
        void display_after() const;
        void display_Vector() const;
        void display_Deque() const;
};
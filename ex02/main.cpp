/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 01:47:12 by lcournoy          #+#    #+#             */
/*   Updated: 2025/12/18 01:47:12 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error: no input numbers provided." << std::endl;
        return 1;
    }

    try
    {
        PmergeMe pm;
        pm.parsing(ac, av);

        pm.display_before();

        // Mesure du temps pour vector
        auto start = std::chrono::high_resolution_clock::now();
        pm.sort_vector();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration_vector = std::chrono::duration<double, std::micro>(end - start).count();

        // Mesure du temps pour deque
        start = std::chrono::high_resolution_clock::now();
        pm.sort_deque();
        end = std::chrono::high_resolution_clock::now();
        auto duration_deque = std::chrono::duration<double, std::micro>(end - start).count();

        pm.display_after();

        std::cout << "Time to process a range of " << ac-1 
                  << " elements with std::vector : " << duration_vector << " us" << std::endl;

        std::cout << "Time to process a range of " << ac-1
                  << " elements with std::deque : " << duration_deque << " us" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

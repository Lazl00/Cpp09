/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:04:08 by lcournoy          #+#    #+#             */
/*   Updated: 2025/12/17 15:04:08 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void    operate(std::stack<int> &stack, char op)
{
    int a;
    int b;

    b = stack.top();
    stack.pop();

    a = stack.top();
    stack.pop();

    if (op == '+')
        stack.push(a + b);
    if (op == '-')
        stack.push(a - b);
    if (op == '*')
        stack.push(a * b);
    if (op == '/')
    {
        if (b == 0)
            throw std::runtime_error("Division by 0 detected.");
        stack.push(a / b); 
    }

}

bool    isoperator(const char c)
{
    if (c == '+' || c == '-' || c == '/' || c == '*')
        return (1);
    return (0);
}

bool    err(const std::string err_msg)
{
    std::cerr << err_msg << std::endl;

    return 0;
}

RPN::RPN() {}

RPN::~RPN() {}

int RPN::getResult() { return (_stack.top()); }

void RPN::compute(const std::string &entry)
{
    std::stringstream stream(entry);
    std::string token;

    while (stream >> token)
    {
        if (token.length() != 1)
            throw std::invalid_argument("Bad entry format detected.");

        if (isdigit(token[0]))
            _stack.push(token[0] - '0');
        else if (isoperator(token[0]) && _stack.size() >= 2)
            operate(_stack, token[0]);
        else
            throw std::invalid_argument("Bad entry format detected.");
    }
    if (_stack.size() != 1)
        throw std::invalid_argument("Bad entry format detected.");
}

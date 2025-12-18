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

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN() {}

int RPN::getResult() { return (_stack.top()); }

void RPN::compute(const char* entry)
{
    std::stack<int> s;

    for (size_t i = 0; entry[i]; ++i)
    {
        char c = entry[i];

        if (c == ' ')
            continue;
        else if (isdigit(c))
            s.push(c - '0');
        else if (isoperator(c))
        {
            if (s.size() < 2)
                throw std::runtime_error("Bad entry format");
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            if (c == '+') s.push(a + b);
            else if (c == '-') s.push(a - b);
            else if (c == '*') s.push(a * b);
            else if (c == '/')
            {
                if (b == 0) throw std::runtime_error("Division by 0");
                s.push(a / b);
            }
        }
        else
            throw std::runtime_error("Bad entry format");
    }

    if (s.size() != 1)
        throw std::runtime_error("Bad entry format");

    _stack = s;
}


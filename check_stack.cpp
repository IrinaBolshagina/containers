#include "stack.hpp"
#include <stack>
#include <iostream>

int main() 
{
	ft::stack<int> ft_stack;
	std::stack<int> std_stack;

	std::cout << std::endl << "checking original std::stack" << std::endl;

	std::cout << std_stack.empty() << std::endl;
	std_stack.push(1);
	std::cout << std_stack.top() << std::endl;
	std_stack.pop();
	std_stack.push(3);
	std_stack.push(5);
	std_stack.push(737);
	while (!std_stack.empty()) 
    { 
        std::cout << std_stack.top() << std::endl; 
        std_stack.pop(); 
    } 

	std::cout << std::endl << "checking my ft::stack" << std::endl;

	std::cout << ft_stack.empty() << std::endl;
	ft_stack.push(1);
	std::cout << ft_stack.top() << std::endl;
	ft_stack.pop();
	ft_stack.push(3);
	ft_stack.push(5);
	ft_stack.push(737);
	while (!ft_stack.empty()) 
    { 
        std::cout << ft_stack.top() << std::endl; 
        ft_stack.pop(); 
    } 
}

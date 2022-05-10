#include "map.hpp"
#include <iostream>

ft::map<char, int> m;

ft::pair<char, int> p1('a', 10);
ft::pair<char, int> p2('b', 20);
ft::pair<char, int> p3('c', 30);
ft::pair<char, int> p4('d', 40);
ft::pair<char, int> p5('e', 50);

ft::map<char, int>::iterator it2;
ft::map<char, int>::iterator it1;
ft::map<char, int>::iterator it;

int main()
{
	m.insert(p3);
	it2 = m._tree.max_node();
	std::cout << "max "<< it2->first << " => " << it2->second << "\n";
	m.insert(p4);
	it2 = m._tree.max_node();
	std::cout << "max "<< it2->first << " => " << it2->second << "\n";
	m.insert(p1);
	it2 = m._tree.max_node();
	std::cout << "max "<< it2->first << " => " << it2->second << "\n";
	m.insert(p2);
	it2 = m._tree.max_node();
	std::cout << "max "<< it2->first << " => " << it2->second << "\n";
	m.insert(p5);
	it2 = m._tree.max_node();
	std::cout << "max "<< it2->first << " => " << it2->second << "\n";

	
	it1 = m.begin();
	std::cout << "begin "<< it1->first << " => " << it1->second << "\n";
	

	for(it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " => " << it->second << "\n";

	// for(int i = 0; i < 10; i++, it++)
	// 	std::cout << it1->first << " => " << it1->second << "\n";

}



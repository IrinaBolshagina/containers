#include "map.hpp"
#include <iostream>
#include <map>
#include "binary_tree.hpp"

typedef ft::map<const char, int>::iterator 	iterator;

ft::map<char, int> m;
ft::map<char, int> m1;
std::map<char, int> m2;

ft::pair<char, int> p1('a', 10);
ft::pair<char, int> p2('b', 20);
ft::pair<char, int> p3('c', 30);
ft::pair<char, int> p4('d', 40);
ft::pair<char, int> p5('e', 50);

std::map<char, int>::iterator it2;
ft::map<char, int>::iterator it1;
ft::map<char, int>::iterator it;

template <class T>
void print_map(T n, std::string name) {
	std::cout << name << ":  \n";	
	for(it = n.begin(); it != n.end(); ++it)
		std::cout << it->first << " => " << it->second << "\n";
	std::cout << std::endl;	

}

ft::node<ft::pair<char, int> > nod;


int main()
{
	m.insert(p3);
	m.insert(p4);
	m.insert(p1);
	m.insert(p2);
	m.insert(p5);

	it1 = m.begin();
	
	std::cout << "!" << typeid(it1).name()   << std::endl;

	// nod = it1;
	std::cout << "begin "<< it1->first << " => " << it1->second << "\n";
	it2 = m2.end();
	std::cout << "end "<< it2->first << " => " << it2->second << "\n";
	print_map(m, "ft::map");
	// --it2;
	// std::cout << it2->first << " => " << it2->second << "\n";

	it1 = m1.begin();
	it1 = m1.end();
	std::cout << "begin "<< it1->first << " => " << it1->second << "\n";
	it1 = m1.end();
	std::cout << "end "<< it2->first << " => " << it2->second << "\n";

	print_map(m1, "ft::map");

	m1 = m;
	// ft::map<char, int> m1(m);
	it = m1.find('c');
	std::cout << it->first << " => " << it->second << "\n";

	// m.clear();
	m1.erase(it);
	print_map(m1, "ft::map1");

	ft::swap(m1, m);

	print_map(m, "ft::map");
	print_map(m1, "ft::map1");

	it = m.lower_bound('a');
	std::cout << it->first << " => " << it->second << "\n";

	it = m.upper_bound('a');
	std::cout << it->first << " => " << it->second << "\n";

	ft::pair<iterator, iterator> p = m.equal_range('a');
	it = p.first;
	std::cout << it->first << " => " << it->second << "\n";
	it = p.second;
	std::cout << it->first << " => " << it->second << "\n";

	std::cout << (m == m1) << "\n";

	// for(it = m1.begin(); it != m1.end(); ++it)
	// 	std::cout << it->first << " => " << it->second << "\n";
	// it1 = ++m1.begin();
	// it2 = m1.end();
	// --it2;
	// m1.erase(it1, it2);
	// print_map(m1, "ft::map1");


}



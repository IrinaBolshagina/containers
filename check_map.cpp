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

ft::map<char, int>::iterator it2;
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
	it2 = m.end();

	it1 = (m.insert(p3)).first;
	std::cout << "p3 iterator " << it1->first << " => " << it1->second << "\n";
	m.insert(p4);
	m.insert(p1);
	m.insert(p2);
	m.insert(p5);
	std::cout << "p3 iterator " << it1->first << " => " << it1->second << "\n";


	it1 = m.begin();
	print_map(m, "ft::map");
	m1 = m;
	it = m1.find('c');
	
	std::cout << "find" << it->first << " => " << it->second << "\n";
	
	it1 = m1.begin();
	m1.erase(it1);
	print_map(m1, "ft::map1");


	// //swap
	std::cout << "m1 begin before swap" << m1.begin().node() << "\n";
	std::cout << "m begin before swap" << m.begin().node() << "\n";
	m1.swap(m);
	std::cout << "m1 begin after swap" << m1.begin().node() << "\n";
	std::cout << "m begin after swap" << m.begin().node() << "\n";
	// swap(m1, m);
	print_map(m, "ft::map");
	print_map(m1, "ft::map1");

	it = m.lower_bound('a');
	std::cout << it->first << " => " << it->second << "\n";

	ft::map<char, int>::const_iterator cit = m.upper_bound('a');
	std::cout << it->first << " => " << it->second << "\n";

	std::cout << (m1 == m) << "\n";


}

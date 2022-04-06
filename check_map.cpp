#include "map.hpp"
#include <map>
#include <iostream>

template <class T, class It>
void print_map(T m, It it, std::string name) {

	std::cout << name << ":  " << std::endl;	
	for(it=m.begin(); it!=m.end(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;
	std::cout << std::endl;	
}


int main() {

	std::cout << std::endl << "  ----------------------      size, empty  ----------------------  " << std::endl << std::endl;
	
	ft::map<char, int> ft_map;
	std::map<char, int> std_map;
	bool emp = std_map.empty();
	std::cout << "std_map is_empty = " << emp << "\n";
	emp = ft_map.empty();
	std::cout << "ft_map  is_empty = " << emp << "\n";
	size_t size = std_map.size();
	std::cout << "std_map size = " << size << "\n";
	size = ft_map.size();
	std::cout << "ft_map  size = " << size << "\n";

	std_map['a']=10;
	std_map['b']=20;
	std_map['c']=30;
	std_map['d']=40;

	std::pair<char, int> p('d', 50);
	std_map.insert(p);

	ft::pair<char, int> p1('d', 50);
	ft_map.insert(p1);

	ft::pair<char, int> p2('d', 60);
	ft_map.insert(p2);

	size = std_map.size();
	std::cout << size << "\n";
	size = ft_map.size();
	std::cout << size << "\n";

	std::map<char, int>::iterator it;
	print_map(std_map, it, "std_map");
	// for(it=std_map.begin(); it!=std_map.end(); ++it)
	// 	std::cout << it->first << " => " << it->second << '\n';

	ft::map<char, int>::iterator it1 = ft_map.begin();
	// char first = it1->first;
	int second = p1.second;
	std::cout << second << '\n';
	std::cout << it1->first << " => " << it1->second << '\n';

}
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

typedef std::map<char, int>::iterator	std_iterator;
typedef ft::map<char, int>::iterator	ft_iterator;


int main() {

	std::cout << std::endl << "  ----------------------   size, empty   ----------------------  " << std::endl << std::endl;
	
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

	std::cout << std::endl << "  ----------------------      insert pair ('e', 50)    ----------------------  " << std::endl << std::endl;

	std::pair<char, int> p('e', 50);
	std::pair<std_iterator, bool> res;
	res = std_map.insert(p);
	std_iterator res1 = res.first;
	std::cout << "return: " << res1->first << " => " << res1->second;
	std::cout << " is inserted: " << res.second << std::endl;

	ft::pair<char, int> p1('e', 50);
	ft::pair<ft_iterator, bool> res_ft;
	res_ft = ft_map.insert(p1);
	ft_iterator ft_it1 = res_ft.first;
	std::cout << "return: " << ft_it1->first << " => " << ft_it1->second;
	std::cout << " is inserted: " << res_ft.second << std::endl;
	
	ft::pair<char, int> p2('f', 60);
	res_ft = ft_map.insert(p2);
	ft_it1 = res_ft.first;
	std::cout << "return: " << ft_it1->first << " => " << ft_it1->second;
	std::cout << " is inserted: " << res_ft.second << std::endl;

	size = std_map.size();
	std::cout << size << "\n";
	size = ft_map.size();
	std::cout << size << "\n";

	std::map<char, int>::iterator it;
	print_map(std_map, it, "std_map");
	// for(it=std_map.begin(); it!=std_map.end(); ++it)
		// std::cout << it->first << " => " << it->second << '\n';
	std::cout << "end " << (--std_map.end())->second << '\n';
	ft::map<char, int>::iterator it1 = ft_map.begin();
	// char first = it1->first;

	// int second = p1.second;
	++it1;
	// std::cout << second << '\n';
	std::cout << it1->first << " => " << it1->second << '\n';
	++it1;
	// std::cout << it1->first << " => " << it1->second << '\n';
	ft_iterator it2 = ft_map.end();
	std::cout << "end "; it2.print_end();
	// std::cout << it2->is_end << "\n";
	std::cout << (it1 == it2) << "\n";
	std::cout << it2->first << " => " << it2->second << '\n';
	

}
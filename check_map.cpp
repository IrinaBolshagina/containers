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

	size = std_map.size();
	std::cout << size << "\n";
	size = ft_map.size();
	std::cout << size << "\n";

	std::map<char, int>::iterator it;
	print_map(std_map, it, "std_map");
	std::cout << "end " << (--std_map.end())->second << '\n';

	
	
	
	std::cout << "\n\nft map\n";
	ft::pair<char, int> p1('a', 10);
	ft::pair<char, int> p2('b', 20);
	ft::pair<char, int> p3('c', 30);
	ft::pair<char, int> p4('d', 40);
	ft::pair<char, int> p5('e', 50);
	
	ft_iterator it1 = ft_map.begin();
	std::cout << "head " << &*it1.node();
	std::cout << " right: " << &*it1.right() << std::endl;
	ft_iterator it2 = ft_map.end();
	std::cout << "end " << &*it2.node() << " "; it2.print_end();
	ft::pair<ft_iterator, bool> res_ft;
	
	res_ft = ft_map.insert(p5);
	ft_iterator ft_it1 = res_ft.first;
	std::cout << "return: " << ft_it1->first << " => " << ft_it1->second;
	std::cout << " is inserted: " << res_ft.second << std::endl; //"node: " << &*it2.node();
	//std::cout << " right: " << &*ft_it1.right() << std::endl;
	it2 = ft_map.end();
	std::cout << "end " << &(*it2) << " "; it2.print_end();
	
	res_ft = ft_map.insert(p2);
	ft_it1 = res_ft.first;
	it2 = ft_map.end();
	std::cout << "end " << &(*it2) << " "; it2.print_end();
	std::cout << "return: " << ft_it1->first << " => " << ft_it1->second;
	std::cout << " is inserted: " << res_ft.second << std::endl; //<< "node: " << &*it2.node();
	// std::cout << " right: " << &*ft_it1.right() << std::endl;
	
	
	// char first = it1->first;

	// int second = p1.second;
	//++it1;
	// std::cout << second << '\n';
	// std::cout << it1->first << " => " << it1->second << '\n';
	// ++it1;
	// std::cout << it1->first << " => " << it1->second << '\n';

	// std::cout << it1->first << " => " << it1->second << '\n';
	it2 = ft_map.end();
	std::cout << "end " << &*it2.node() << " "; it2.print_end();
	// std::cout << it2->is_end << "\n";
	// std::cout << (it1 == it2) << "\n";
	// std::cout << it2->first << " => " << it2->second << '\n';
	
	res_ft = ft_map.insert(p1);
	ft_it1 = res_ft.first;
	std::cout << "return: " << ft_it1->first << " => " << ft_it1->second;
	std::cout << " is inserted: " << res_ft.second << std::endl;
	
	it2 = ft_map.end();
	std::cout << "end " << &(*it2) << " "; it2.print_end();

	res_ft = ft_map.insert(p4);
	ft_it1 = res_ft.first;
	std::cout << "return: " << ft_it1->first << " => " << ft_it1->second;
	std::cout << " is inserted: " << res_ft.second << std::endl;
	
	it2 = ft_map.end();
	std::cout << "end " << &*it2.node() << " "; it2.print_end();

	res_ft = ft_map.insert(p4);
	ft_it1 = res_ft.first;
	std::cout << "return: " << ft_it1->first << " => " << ft_it1->second;
	std::cout << " is inserted: " << res_ft.second << std::endl;
	it1 = ft_map.begin();
	// for(int i = 0; i < 4; ++i, ++it1)
	// 	std::cout << &(*it1) << it1->first << " => " << it1->second << '\n';

	ft_map['c'] = 30; 

	for(it1 = ft_map.begin(); it1 != ft_map.end(); it1++) {
		std::cout << &*it1.node() << " " << it1->first << " => " << it1->second << '\n';
		std::cout << " right: " << &(*it1.node()->right) << std::endl;
	}
	it2 = ft_map.end();
	std::cout << "end " << &*it2.node() << " "; it2.print_end();
	
	it2--;
	for(; it2 != ft_map.begin(); it2--) {
		std::cout << &*it2.node() << " " << it2->first << " => " << it2->second << '\n';
		std::cout << " right: " << &(*it2.node()->right) << std::endl;
	}
	std::cout << "end-- " << it2->first << " => " << it2->second << std::endl;

	ft_iterator it_find = ft_map.find('d');
	// std::cout << "\nfind: " << it_find->first << " => " << it_find->second << std::endl;

	// it_find = ft_map.find('x');
	// std::cout << "find: " << it_find->first << " => " << it_find->second << std::endl;

	ft_map.erase(it_find);
	for(it1 = ft_map.begin(); it1 != ft_map.end(); ++it1) {
		std::cout << it1->first << " => " << it1->second << '\n';
	}
	std::cout << '\n';
	it_find = ft_map.find('c');
	ft_map.insert(it_find, p4);
	for(it1 = ft_map.begin(); it1 != ft_map.end(); ++it1) {
		std::cout << it1->first << " => " << it1->second << '\n';
	}



	// ft_map.clear();
	// std::cout << ft_map.empty() << '\n';
	// ft_map['c'] = 30; 

	// for(it1 = ft_map.begin(); it1 != ft_map.end(); ++it1) {
	// 	std::cout << it1->first << " => " << it1->second << '\n';
	// }

	// std_iterator itb = std_map.begin();
	// --itb;
	// std::cout << itb->first << " => " << itb->second << '\n';

	// ft_iterator itbf = ft_map.begin();
	// --itbf;
	// std::cout << itbf->first << " => " << itbf->second << '\n';



}
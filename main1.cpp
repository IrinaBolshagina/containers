#include <map>
#include "map.hpp"
#include <vector>


int main() {


   std::vector<int> v;
   std::map<int, int> mp1;

    for (int i = 0, j = 10; i < 20; ++i, ++j) {
        mp1.insert(std::make_pair(i, j));
    }
    // g_start1 = timer();
    std::map<int, int> mp12(mp1.begin(), mp1.end());
	std::map<int, int>::iterator it1 = mp1.begin();
    // g_end1 = timer();
    for (int i = 0; i < 20; ++i, it1++) {
        v.push_back(it1->first);
        v.push_back(it1->second);
    }
    // return v;

	std::cout << "original\n";
	for(it1 = mp1.begin(); it1 != mp1.end(); ++it1)
		std::cout << it1->first << " => " << it1->second << '\n';

	std::cout << "copy\n";
	for(it1 = mp12.begin(); it1 != mp12.end(); ++it1)
		std::cout << it1->first << " => " << it1->second << '\n';

	std::cout << "vector\n";
	for ( int i = 0; i < v.size(); ++i)
		std::cout << v[i] << " ";


	int _ratio = 10000;
    // std::vector<int> v;
	ft::map<int, int> mp;

    for (int i = 0, j = 10; i < 20; ++i, ++j) {
        mp.insert(ft::make_pair(i, j));
    }

    // g_start2 = timer();
    ft::map<int, int> mp2(mp.begin(), mp.end());
    // g_end2 = timer();
    ft::map<int, int>::iterator it = mp2.begin();
    for (int i = 0; i < 20; ++i, it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }

	std::cout << "original\n";
	for(it = mp.begin(); it != mp.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "copy\n";
	for(it = mp2.begin(); it != mp2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "vector\n";
	for ( int i = 0; i < v.size(); ++i)
		std::cout << v[i] << " ";

	
    // return v;
}
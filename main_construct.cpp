#include "map.hpp"
#include <map>
#include <vector>

ft::map<int, int> mp;

int main() {

    std::vector<int> v;

    for (int i = 0, j = 10; i < 200; ++i, ++j) {
        mp.insert(ft::make_pair(i, j));
    }
   
   	ft::map<int, int> mp2(mp.begin(), mp.end());
    ft::map<int, int>::iterator it = mp2.begin();
    for (int i = 0; i < 200; ++i, it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }

	for(it = mp2.begin(); it != mp2.end(); ++it)
		std::cout << it->first << " => " << it->second << "\n";
	std::cout << std::endl;	
    // return v;
}

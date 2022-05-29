#include "map.hpp"
#include "utility.hpp"
#include <map>
#include <vector>
#include <iostream>

ft::map<int, int> mp;

int main() {


std::vector<int> v;

    mp.insert(ft::make_pair(10, 10));
    mp.insert(ft::make_pair(20, 20));
    mp.insert(ft::make_pair(30, 30));
    mp.insert(ft::make_pair(40, 40));
    mp.insert(ft::make_pair(50, 50));
    mp.insert(ft::make_pair(60, 60));
    // g_start1 = timer();
    const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair = mp.equal_range(10);
    const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair2 = mp.equal_range(11);
    const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair3 = mp.equal_range(1);
    // g_end1 = timer();
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second->first);
    v.push_back(pair.second->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second->first);
    v.push_back(pair2.second->second);
    v.push_back(pair3.first->first);
    v.push_back(pair3.first->second);
    v.push_back(pair3.second->first);
    v.push_back(pair3.second->second);
}
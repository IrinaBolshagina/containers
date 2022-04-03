#include "map.hpp"
#include <map>

int main() {
	ft::map<char, int> ft_map;
	std::map<char, int> std_map;
	bool emp = std_map.empty();
	std::cout << emp << "\n";
	emp = ft_map.empty();
	std::cout << emp << "\n";
	size_t size = std_map.size();
	std::cout << size << "\n";
	size = ft_map.size();
	std::cout << size << "\n";

}
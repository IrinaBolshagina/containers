#include <iostream>
#include <vector>
#include "vector.hpp"

template <typename T>
void print(ft::vector<T> v, std::string name) {

	std::cout << name << ":  ";	
	for ( int i = 0; i < v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << std::endl;	

}


int main() 

{

	std::vector<int> std_vector;
	std::vector<int> std_vector2;

	std::cout << std::endl << "checking original std::vector" << std::endl;

	for ( int i = 0; i < 1; i++)
		std_vector.push_back(i + 1);
	std::cout << "v1:\n";
	for ( int i = 0; i < 10; i++)
		std::cout << std_vector[i] << " ";
		std::cout << std::endl;

	for ( int i = 0; i < 10; i++)
		std_vector2.push_back(i);
	std::cout << "v2:\n";
	for ( int i = 0; i < 10; i++)
		std::cout << std_vector2[i] << " ";
		std::cout << std::endl;
	bool dif = std_vector > std_vector2;

	std::cout << "v1 > v2? " << dif << std::endl;

	std::cout << "size: " << std_vector.size() << std::endl;
	std::cout << "cap: " << std_vector.capacity() << std::endl;

	std_vector.resize(38);
	std::cout << "size: " << std_vector.size() << std::endl;
	std::cout << "cap: " << std_vector.capacity() << std::endl;
	
	for ( int i = 0; i < 10; i++)
		std::cout << std_vector[i] << " ";
		std::cout << std::endl;

	std::cout << std_vector.max_size() << std::endl;



	std::cout << std::endl << "checking my fucking ft::vector" << std::endl;

	int i = 12;
	size_t n = 10;
	ft::vector<int> ft_vector;
	std::cout << ft_vector.empty() << std::endl;
	ft::vector<int> ft_vector2;
	
	for ( int i = 0; i < 15; i++)
		ft_vector.push_back(i + 1);
	std::cout << "v1:\n";
	for ( int i = 0; i < ft_vector.size(); i++)
		std::cout << ft_vector[i] << " ";
		std::cout << "\n";
	std::cout << "front: " <<ft_vector.front() << std::endl;
	std::cout << "back: " <<ft_vector.back() << std::endl;
	std::cout << "at(5): " <<ft_vector.at(5) << std::endl;
	ft_vector2 = ft_vector;
	for ( int i = 0; i < 16; i++)
		ft_vector2.push_back(i);
	std::cout << "v2:\n";
	for ( int i = 0; i < ft_vector2.size(); i++)
		std::cout << ft_vector2[i] << " ";
		std::cout << std::endl;
	bool dif2 = ft_vector > ft_vector2;

	std::cout << "v1 > v2? " << dif2 << std::endl;
	std::cout << std::endl;
	std::cout << "size: " << ft_vector.size() << std::endl;
	std::cout << "cap: " << ft_vector.capacity() << std::endl;
	ft_vector.pop_back();
	ft_vector.resize(38, 1);
	for ( int i = 0; i < ft_vector.size(); i++)
		std::cout << ft_vector[i] << " ";
	std::cout << std::endl;
	ft_vector.reserve(120);
	std::cout << "size: " << ft_vector.size() << std::endl;
	std::cout << "cap: " << ft_vector.capacity() << std::endl;
	std::cout << ft_vector.empty() << std::endl;

	swap(ft_vector2, ft_vector);
	std::cout << "v1:  ";
	for ( int i = 0; i < ft_vector.size(); i++)
		std::cout << ft_vector[i] << " ";
		std::cout << "\n";

	std::cout << "v2:  ";
	for ( int i = 0; i < ft_vector2.size(); i++)
		std::cout << ft_vector2[i] << " ";
		std::cout << std::endl;

	ft_vector2.swap(ft_vector);
	std::cout << "v1:  ";
	for ( int i = 0; i < ft_vector.size(); i++)
		std::cout << ft_vector[i] << " ";
		std::cout << "\n";

	std::cout << "v2:  ";
	for ( int i = 0; i < ft_vector2.size(); i++)
		std::cout << ft_vector2[i] << " ";
		std::cout << std::endl;
	
	bool dif3 = ft_vector == ft_vector2;
	std::cout << "v1 == v2? " << dif3 << std::endl;

	std::cout << ft_vector.max_size() << std::endl;

	// iterators

	ft::vector<int>::iterator it = ft_vector.begin();
	std::cout << *it << std::endl;
	// *it = 21; 

	for ( int i = 0; i < ft_vector.size(); i++)
		std::cout << ft_vector[i] << " ";
		std::cout << "\n";

	std::cout << *(it + 10) << std::endl;

	ft::vector<int>::iterator it5 = it + 5;
	std::cout << *(it5) << std::endl;

	std::cout << "v1:  ";
	for ( int i = 0; i < ft_vector.size(); i++)
		std::cout << ft_vector[i] << " ";
		std::cout << std::endl;


	/*	----------------------   insert  -----------------------   */

	// std::cout << std::endl << "  ----------------------      insert 1000 to position 2  ----------------------  " << std::endl << std::endl;
	
	// ft::vector<int>::iterator it2 = ft_vector.begin() + 2;
	// ft::vector<int>::iterator it_insert =  ft_vector.insert (it2, 1000);
	// print(ft_vector, "v1");
	// std::cout << "return iterator at value: " << *(it_insert) << std::endl;

	// std::cout << std::endl << "  ----------------------   insert 10 times value 2 to position 5  ----------------------  " << std::endl << std::endl;

	// it5 = ft_vector.begin() + 5;
	// ft_vector.insert (it5, 10, 2);
	// print(ft_vector, "v1");
	
	std::cout << std::endl << "  -------------------  insert from v2 range 4 - 10 to position 1 of v1 -----------------  " << std::endl << std::endl;

	ft::vector<int>::iterator it_start = ft_vector2.begin() + 4;
	ft::vector<int>::iterator it_end = ft_vector2.begin() + 10;
	ft::vector<int>::iterator it1 = ft_vector.begin() + 1;
	ft_vector.insert(it1, it_start, it_end);
	print(ft_vector, "v1");


	/*	----------------------   erase  -----------------------   */

	std::cout << std::endl << "  ----------------------         erase 8d element         ----------------------  " << std::endl << std::endl;
	ft::vector<int>::iterator it8 = ft_vector.begin() + 8;
	ft::vector<int>::iterator it_erase = ft_vector.erase(it8);
	print(ft_vector, "v1");
	std::cout << "return iterator at value: " << *(it_erase) << std::endl;


	std::cout << std::endl << "  ----------------------    erase range 5 - 24 elements    ----------------------  " << std::endl << std::endl;
	it5 = ft_vector.begin() + 5;
	ft::vector<int>::iterator it24 = ft_vector.begin() + 24;
	it_erase = ft_vector.erase(it5, it24);
	print(ft_vector, "v1");
	std::cout << "return iterator at value: " << *(it_erase) << std::endl;

	ft::vector<int>::iterator it3 = ft_vector.begin() + 3;
	ft::vector<int>::iterator it10 = ft_vector.begin() + 10;
	ft::vector<int> ft_vector3(it3, it10);
	print(ft_vector3, "v3");
}
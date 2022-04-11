#include "vector.hpp"
#include <vector>

int main() {
	std::vector<int> vector;

    std::vector<int>::iterator it;
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        vector.push_back(i);
    it = vector.begin();

    v.push_back(*(++it));
    v.push_back(*(--it));
    v.push_back(*(it + 1));
    it += 1;
    v.push_back(*(it - 1));
    it -= 1;
    v.push_back(*it);

	ft::vector<int> vector2;
    ft::vector<int>::iterator it2;
    std::vector<int> v2;
    for (int i = 0; i < 10; ++i)
        vector2.push_back(i);
    it2 = vector2.begin();
    v2.push_back(*(++it2));
    v2.push_back(*(--it2));
    v2.push_back(*(it2 + 1));
    it2 += 1;
    v2.push_back(*(it2 - 1));
    it2 -= 1;
    v2.push_back(*it2);


	for (it = v.begin(); it < v.end(); ++it)
        std::cout << *it << " ";
	std::cout << std::endl;

	for (it = v2.begin(); it < v2.end(); ++it)
        std::cout << *it << " ";
	std::cout << std::endl;


//     std::vector<int> v;
//     vector.assign(1000, 1);
//     vector.insert(vector.end() - 50, 4200 * 10000 , 2);
//     v.push_back(vector[2121]);
//     v.push_back(vector.size());
//     v.push_back(vector.capacity());
//     return v;


}

// 		std::vector<int> v;
// 		vector.assign(1000, 1);
// 		g_start2 = timer();
// 		vector.insert(vector.end() - 50, 4200 * 10000 , 2);
// 		g_end2 = timer();
// 		v.push_back(vector[2121]);
// 		v.push_back(vector.size());
// 		v.push_back(vector.capacity());
// 		return v;
// }

// int main() {

//     exit(run_vector_unit_test<int>("insert(fill)", insert_test_2, insert_test_2));
// }
// }


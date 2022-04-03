#include "binary_tree.hpp"

int main() {

	ft::Tree<int> tree;
	int n = 13, d = 12, c = 14;

	tree.insert_val(n);
	tree.insert_val(d);
	tree.insert_val(c);
	tree.insert_val(20);
	tree.insert_val(10);
	for (int i = 1; i < 10; i++)
		tree.insert_val(i);
	tree.print_tree();
	std::cout << "size = " << tree.size() << std::endl;

}


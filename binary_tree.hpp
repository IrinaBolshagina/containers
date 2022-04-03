#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

#include <iostream>

namespace ft {

	template <class T>
	class Tree {

		public:
		//	Member types
			typedef T			value_type;
			typedef size_t		size_type;

		//	Tree node struct
		struct node {
			public:
				value_type	value;
				node		*left;
				node		*right;
				node		*parent;
			public:
				node() : value(), left(NULL), right(NULL), parent(NULL) {}
				node(const value_type &val) : value(val), left(NULL), right(NULL), parent(NULL) {}
				~node() {}
				node(const node& other) { *this = other; }
				node &operator=(const node& other) {
					if (*this != other) {
					value = other.value;
					left = other.left;
					right = other.right;
					parent = other.parent;
					}
					return (*this);
				}
		};	//	struct node

		public:
			node	 	*root;
			node		*head;
			size_type	_size;
			Tree() : _size(0), root(new(node)) { head = root; }
			~Tree() { delete root; }

		// private:

			bool	isEmpty() const { return root == head; }

			bool	search(node *root, value_type val) {
				if (root == NULL)
					return false;
				if (val < root->value)
					search(root->left, val);
				else if (val > root->value)
					search(root->right, val);
				else if (root->value == val)
					return true;
			}

			size_type	size(node *root) const {
				if (root == head)
					return 0;
				else if (root != NULL)
					return (1 + size(root->left) + size(root->right));
				else return 0;
			}

			size_type	size() const {
				return size(root);
			}

			void insert(node *&root, node *new_node)
			{
				if (root == NULL)
					root = new_node;
				else
				{
					if (new_node->value < root->value)
						insert(root->left, new_node);

					else insert(root->right, new_node);
				}
			}

			void insert_val(value_type const &val)
			{
				if (head == root)
					root = new node(val);
				else
					insert (root, new node(val));
			}

			node *insert_to_node(node *root, node *new_node) {
				if (new_node->value == root->value){
					if (root->left != NULL)
						return (insert_to_node(root->left, new_node));
					root->left = new_node;
				}
				else{
					if (root->right != NULL)
						return (insert_to_node(root->right, new_node));
					root->right = new_node;
				}
				new_node->parent = root;
				return (new_node);
			}
	
			void print(node *root) {
				if (root == NULL)
					return;
				print(root->left);
				std::cout << root->value << std::endl;
				print(root->right);
			}

			void print_tree() {
				print(root);
			}






	};	//	class Tree	

}	//	namespace ft

#endif

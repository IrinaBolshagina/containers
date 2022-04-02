#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

#include <iostream>

namespace ft {

	template <class T>
	class node {
		public:
			typedef T		value_type;
		private:
			value_type		value;
			node			*left;
			node			*right;
			node			*parent;

		public:

			bool search(node *root, value_type val) {
				if (root == NULL)
					return false;
				if (val < root->value)
					search(root->left, val);
				else if (val > root->value)
					search(root->right, val);
				else if (root->value == val)
					return true;
			}

			node *insert(node *new_node) {
			if (root == header)
				root = new_node;
			else
				insert_to_node(root, new_node);
			return new_node;	
			}

			node_pointer	_insert_to_node(node_pointer root, node_pointer new_node){
			if (_compare(*new_node->value, *root->value)){
				if (!is_nil(root->left))
					return (_insert_to_node(root->left, new_node));
				root->left = new_node;
			}
			else{
				if (!is_nil(root->right))
					return (_insert_to_node(root->right, new_node));
				root->right = new_node;
			}
			new_node->parent = root;
			return (new_node);
		}

			void insert(node *root, value_type val) {
				if (root == NULL) {
					root->value = val;
					left = NULL;
					right = NULL;
				}
				if (val < root->value)
					insert(root->left, val);
				else if (val > root->value)
					insert(root->right, val);
				else if (val == root->value)
					insert(root->right, val);				
			}

			void print(node *root) {
				if (root == NULL)
					return;
				print(root->left);
				std::cout << root->value << std::endl;
				print(root->right);
			}






	};	//	node





	

}	//	namespace ft

#endif

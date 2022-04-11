#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

#include <iostream>
#include "utility.hpp"

namespace ft {

	template < class Value, class Allocator = std::allocator<Value> >
	// template  <	class Key,														
	// 		class T,														
	// 		class Compare = std::less<Key>,									
	// 		class Allocator = std::allocator<ft::pair<const Key, T> > > 
	struct node {
			public:
				// typedef Key											key_type;
				// typedef T											mapped_type;
				// typedef ft::pair <const key_type, mapped_type>		value_type;
				typedef Value										value_type;
				typedef Allocator									allocator_type;
				// typedef Compare										key_compare;
				typedef typename allocator_type::size_type			size_type;

	
			// private:
				allocator_type	_alloc;
				value_type		*value;
				node			*left;
				node			*right;
				node			*parent;
				bool			is_end;

			public:
				// node() : value(), left(NULL), right(NULL), parent(NULL) {}
				node() : left(NULL), right(NULL), parent(NULL), is_end(false) {
					value = _alloc.allocate(1); //(sizeof(value_type));
					_alloc.construct(value, *(new value_type()));
				}

				node(const value_type &val) : left(NULL), right(NULL), parent(NULL), is_end(false) {
					value = _alloc.allocate(sizeof(value_type));
					_alloc.construct(value, val);
				}

				~node() {
					_alloc.destroy(value);
					_alloc.deallocate(value, 1);
				}

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

				node* tree_min() {
					node *n = this;
					while(n->left != NULL)
						n = n->left;
					return n;
				}

				node* tree_max() {
					node *n = this;
					while (n->right != NULL)
						n = n->right;
					return n;
				}

				node* successor() {
					node *n = this;
					if (n->right) {
						return n->right->tree_min();
					}
					else {
						node *y = n->parent;
						while (y != NULL && n == y->right) {
							n = y;
							y = y->parent;
						}
						return y;
					}
				}


		};	//	struct node


	template  <	class Key, class T,	
				class Compare = std::less<Key>,									
				class Allocator = std::allocator<ft::pair<const Key, T> > > 
	// template < class Value, class Allocator = std::allocator<Value> >
	class Tree {

		public:
		//	Member types
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair <const key_type, mapped_type>		value_type;
			typedef Allocator									allocator_type;
			typedef Compare										key_compare;
			typedef typename allocator_type::size_type			size_type;
			typedef node <value_type, allocator_type>			node;

		//	Tree node struct
		
		// private:
			node			*root;
			node			*head;
			node            *end;
			size_type		_size;
			allocator_type	_alloc;
			key_compare		_comp;

		public:
			Tree(const allocator_type& alloc = allocator_type()) : _size(0), _alloc(alloc), root(new(node)), end(new(node)) 
			{
				// root = _alloc.allocate(1);
				// _alloc.construct(root, node());
				// head = new node();
				head = root;
				// end = new node();
				end->is_end = true;
				head->parent = end;
			}
			~Tree() //{}
			{ 
				delete root;
				delete end; 
				if (head!=root)
					delete head;
			}

			node *end_node() { return end; }
			node *head_node() { return head; }

			bool	isEmpty() const { return root == head; }

			// bool	search(node *root, value_type val) {
			// 	if (root == NULL)
			// 		return false;
			// 	if (val < root->value)
			// 		search(root->left, val);
			// 	else if (val > root->value)
			// 		search(root->right, val);
			// 	else if (root->value == val)
			// 		return true;
			// }

			node	*find(node *root, value_type *val) {
				if (root == end)
					return end;
				if (val->first < root->value->first)
					search_key(root->left, val->first);
				else if (val->first > root->value->first)
					search_key(root->right, val->first);
				else if (root->value->first == val->first)
					return root;
				return end;
			}

			node	*find(value_type val) {
				return find(root, &val);
			}

			// переписать на compare
			bool	search_key(node *root, const key_type &key) {
				if (root == NULL)
					return false;
				if (key < root->value->first)
					search_key(root->left, key);
				else if (key > root->value->first)
					search_key(root->right, key);
				else if (root->value->first == key)
					return true;
				return false;
			}

			bool	search_key(const key_type &key) {
				return search_key(root, key);
			}

			// node	*max_node(node *root) {
			// 	if (root->right == NULL)
			// 		return root;
			// 	else
			// 		return max_node(root->right);
			// }

			// node	*max_node() {
			// 	return max_node(root);
			// }

			node	*max_node() {
				return head->tree_max();
			}

			// node	*min_node(node *root) {
			// 	if (root->left == NULL)
			// 		return root;
			// 	else
			// 		return min_node(root->left);
			// }

			// node	*min_node() {
			// 	return min_node(root);
			// }

			node	*min_node() {
				return head->tree_min();
			}

			size_type	size(node *root) const {
				if (root == head)
					return 0;
				else if (root != NULL)
					return (1 + size(root->left) + size(root->right));
				else return 0;
			}

			size_type	size() const {
				// return size(head);
				return _size;
			}

			// void insert(node *&root, node *new_node)
			// {
			// 	if (root == NULL)
			// 		root = new_node;
			// 	else
			// 	{
			// 		if (*(new_node->value) < *(root->value))
			// 			insert(root->left, new_node);

			// 		else 
			// 			insert(root->right, new_node);
			// 	}
			// }

			// // void insert_end() {
			// // 	if (end != root && end->parent != max_node()) {
			// // 		node
			// // 		_alloc.destroy(end);
			// // 		_alloc.deallocate(end, 1);
			// // 		end->parent->right = NULL;
			// // 		// node* tmp = max_node();
			// // 		// tmp->right = end;
			// // 		// end->parent = tmp;
			// // 	}
			// // }

			// node *insert_val(value_type const &val)
			// {
			// 	node *new_node = new node(val);
			// 	if (head == root)
			// 		root = new_node;
			// 	// else if (val > max_node()->value) {
			// 	// 	delete end;
			// 	// 	end = new_node;
			// 	// 	new_node->right = end;
			// 	// }
			// 	else
			// 		insert (root, new_node);
			// 	++_size;

			// 	return new_node;
			// }

			// node *insert_to_node(node *root, node *new_node) {
			// 	if (new_node->value == root->value){
			// 		if (root->left != NULL)
			// 			return (insert_to_node(root->left, new_node));
			// 		root->left = new_node;
			// 	}
			// 	else{
			// 		if (root->right != NULL)
			// 			return (insert_to_node(root->right, new_node));
			// 		root->right = new_node;
			// 	}
			// 	new_node->parent = root;
			// 	return (new_node);
			// }


		void insert(node *&root, node *new_node)
		{
			if (root == NULL)
				root = new_node;
			else
			{
				if (_comp(new_node->value->first, root->value->first))
					insert(root->left, new_node);

				else 
					insert(root->right, new_node);
			}
		}

		node *insert_val(value_type const &val)
		{
			node *new_node = new node(val);
			if (head == root)
				root = new_node;
			else {
				node *max = max_node();
				if (_comp(max->value->first, val.first)) {
					delete(end);
					node *max = max_node();
					max->right = new_node;
					end = new node();
					new_node->right = end;
					end->is_end = true;
				}
				else
					insert (root, new_node);
			}
			++_size;
			return new_node;
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

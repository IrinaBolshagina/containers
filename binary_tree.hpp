#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

#include <iostream>
#include "utility.hpp"

namespace ft {

	template < class Value, class Allocator = std::allocator<Value> >
	struct node {
			public:
				typedef Value										value_type;
				typedef Allocator									allocator_type;
				typedef typename allocator_type::size_type			size_type;

	
				allocator_type	_alloc;
				value_type		*value;
				node			*left;
				node			*right;
				node			*parent;
				bool			is_end;

			public:
				node() : left(NULL), right(NULL), parent(NULL), is_end(false) {
					value = _alloc.allocate(sizeof(value_type));
					_alloc.construct(value, value_type());
				}

				node(const value_type &val) : left(NULL), right(NULL), parent(NULL), is_end(false) {
					value = _alloc.allocate(sizeof(value_type));
					_alloc.construct(value, val);
				}

				~node() {
					_alloc.destroy(value);
					_alloc.deallocate(value, sizeof(value_type));
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
					while (n->right != NULL && !n->right->is_end)
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
		
		private:
			node			*head;
			node            *end;
			size_type		_size;
			allocator_type	_alloc;
			key_compare		_comp;

		public:
			Tree(const allocator_type& alloc = allocator_type()) : _size(0), _alloc(alloc)
			{
				head = new node();
				end = new node();
				end->is_end = true;

			}
			~Tree() 
			{ 
				del_tree(head);	
				// delete head;
				// delete end;
			}

			void del_tree(node *root) {
				if (root) {
					del_tree(root->left);
					del_tree(root->right);
					delete root;
				}
			}
			
			node *end_node() { return end; }
			node *head_node() { return head; }

			bool	isEmpty() const { return _size == 0; }

			// node	*find(node *root, value_type *val) { // два раза проходит почему-то
			// 	node *res;
			// 	if (root == NULL)
			// 		res = NULL;
			// 	if (val->first < root->value->first)
			// 		find(root->left, val);
			// 	else if (val->first > root->value->first)
			// 		find(root->right, val);
			// 	else if (root->value->first == val->first)
			// 		res = root;
			// 	return res;
			// }

			// node	*find(value_type val) {
			// 	return find(head, &val);
			// }

			node*	search(node* root, const key_type& key) const {
				if (root == NULL || root->value->first == key)
					return root;
				if (_comp(key, root->value->first))
					return search(root->left, key);
				return search(root->right, key);
			}

			node*	search(const value_type& val) const {
				return search(head, val.first);
			}

			// переписать на compare
			// bool	search_key(node *root, const key_type &key) {
			// 	if (root == NULL)
			// 		return false;
			// 	if (_comp(key, root->value->first))
			// 		search_key(root->left, key);
			// 	else if (_comp(root->value->first, key))
			// 		search_key(root->right, key);
			// 	else
			// 		return true;
			// }

			// bool	search_key(const key_type &key) {
			// 	return search_key(head, key);
			// }

			node	*max_node() {
				return head->tree_max();
			}

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

		node *insert_to_node(node* root, node* new_node) {
			if (_comp(new_node->value->first, root->value->first)){
				if (root->left)
					return (insert_to_node(root->left, new_node));
				root->left = new_node;
			}
			else{
				if (root->right)
					return (insert_to_node(root->right, new_node));
				root->right = new_node;
			}
			new_node->parent = root;
			return (new_node);
		}

		node *insert_val(value_type const &val)
		{
			if (_size == 0) {
				delete head;
				head = new node(val);
				head->right = end;
				end->parent = head;
				++_size;
				return head;
			}
			else {
			node *new_node = new node(val);
			node *max = max_node();
			if (_comp(max->value->first, val.first)) {
				node *tmp = end;
				max->right = new_node;
				new_node->parent = max;
				end = tmp;
				new_node->right = end;
				end->parent = new_node;
			}
			else
				insert_to_node(head, new_node);				
			++_size;
			return new_node;
			}
		}

	};	//	class Tree	

}	//	namespace ft

#endif

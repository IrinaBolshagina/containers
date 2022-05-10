#ifndef BINARY_TREE_HPP
# define BINARY_TREE_HPP

#include <iostream>
#include "utility.hpp"

namespace ft {

	template < class Value, class Allocator = std::allocator<Value> >
	struct node {
			public:
			//	Member types
				typedef Value										value_type;
				typedef Allocator									allocator_type;
				typedef typename allocator_type::size_type			size_type;

				allocator_type	_alloc;
				value_type		*value;
				node			*left;
				node			*right;
				node			*parent;
				bool			is_leaf;
				// bool			is_end;
				// bool			is_begin;

			public:
				node() : left(NULL), right(NULL), parent(NULL), is_leaf(false) {
					value = _alloc.allocate(sizeof(value_type));
					_alloc.construct(value, value_type());
				}

				node(const value_type &val) : left(NULL), right(NULL), parent(NULL), is_leaf(false) {
					value = _alloc.allocate(sizeof(value_type));
					_alloc.construct(value, val);
				}

				~node() {
					_alloc.destroy(value);
					_alloc.deallocate(value, sizeof(value_type));
				}

				node(const node& other) { *this = other; }

				node&	operator=(const node& other) {
					if (this == &other)
						return *this;
					value = other.value;
					left = other.left;
					right = other.right;
					parent = other.parent;
					is_leaf = other.is_leaf;
					return *this;
				}

				// void set_value(const value_type& val) {
				// 	*value = val;
				// }

				node*	tree_min() { 
					node *n = this;
					// while(n->left != NULL && !n->left->is_begin)
					while(n->left->is_leaf == false)
						n = n->left;
					return n;
				}

				node*	tree_max() {
					node *n = this;
					while (n->right->is_leaf == false) 
						n = n->right;
					return n;
				}

				node* find_root() {
					node *n = this;
					while (n->parent != NULL) 
						n = n->parent;
					return n;
				}

				node*	successor() {
					node *n = this;
					if (find_root()->tree_max() == n)
						return n->right;
					if (n->right->is_leaf == false)
						return n->right->tree_min();
					node *y = n->parent;
					while (y != NULL && n == y->right) {
						n = y;
						y = y->parent;
					}
					return y;
				}

				node*	predecessor() {
					node *n = this;
					// if (find_root()->tree_min() == n)
					// 	return n->left;
					if (n->left->is_leaf == false) {
						return n->left->tree_max();
					}
					node *y = n->parent;
					while (y != NULL && n == y->left) {
						n = y;
						y = y->parent;
					}
					return y;

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
			// node            *end;
			// node			*begin;
			key_compare		_comp;
			allocator_type	_alloc;
			size_type		_size;

		public:
		
			Tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : 
			_comp(comp), _alloc(alloc), _size(0)  {
				head = new node(value_type()); // так будет работать? -да
				head->is_leaf = true;
				// end = new node();
				// begin = new node();
				// head->right = end;
				// end->parent = head;
				// end->is_end = true;
				// head->left = begin;
				// begin->parent = head;
				// begin->is_begin = true;
			}

			Tree&	operator= (const Tree& other) {
				if (this == &other)
					return *this;
				del_tree(head);
				this->head = this->clone(other.head);
				// this->begin = min_node()->left;
				// this->end = max_node()->right;
				this->_size = other._size;
				this->_alloc = other._alloc;
				this->_comp = other._comp;	
				return *this;
			}

			~Tree() { del_tree(head); }

			void	del_tree(node *root) {
				if (root) {
					del_tree(root->left);
					del_tree(root->right);
					delete root;
				}
			}

			void	clear() {
				// if (_size > 0) {
					del_tree(head);
					_size = 0;
					head = new_node();
					// end = new node();
					// begin = new node();
					// head->right = end;
					// end->parent = head;
					// end->is_end = true;
					// head->left = begin;
					// begin->parent = head;
					// begin->is_begin = true;
				// }
			}

						//	create new node with value and leafs
			node* new_node(const value_type& val = value_type()) {
				node *n = new node(val);
				n->left = new node(); 		//	left leaf
				n->left->is_leaf = true;
				n->left->parent = n;
				n->right = new node();		//	right leaf
				n->right->is_leaf = true;
				n->right->parent = n;
				return n;
			}

			node	*copy_node(node *src) {
				node *res = new node(*src->value);
				res->is_leaf = src->is_leaf; // убрала end, begin
				return res;
			}

			node	*clone(node *src) {
				node *res = copy_node(src);
				if (src->left) { // && !src->left->is_begin) {
					res->left = clone(src->left);
					res->left->parent = res;
				}
				if (src->right) {
					res->right = clone(src->right);
					res->right->parent = res;
				}
				return res;
			}
			
			node*	head_node() { return head; }

			node*	end_node() { return max_node()->right; }

			node*	begin_node() { return min_node()->left; }

			bool	empty() const { return _size == 0; }

			node*	search(node* root, const key_type& key) const {
				// if (root == NULL || (root->value->first == key && !root->is_begin && !root->is_end)) 
				if (root->is_leaf == true)
					return NULL;
				if (root->value->first == key && root->is_leaf == false)
					return root;
				if (_comp(key, root->value->first))
					return search(root->left, key);
				return search(root->right, key);
			}

			node*	search(const value_type& val) const {
				if (_size == 0)
					return NULL;
				return search(head, val.first);
			}

			node*	max_node() { return head->tree_max(); }

			node*	min_node() { return head->tree_min(); }

			size_type	size() const {
				return _size;
			}

			node*	insert_node(node* root, node* new_node) {
				if (_comp(new_node->value->first, root->value->first)) {
					if (root->left->is_leaf == false)
						return (insert_node(root->left, new_node));
					delete(root->left);
					root->left = new_node;
				}
				else {
					if (root->right->is_leaf == false)
						return (insert_node(root->right, new_node));
					delete(root->right);
					root->right = new_node;
				}
				new_node->parent = root;
				return (new_node);
			}

			//	inserts right child to parent node
			node*	insert_val(node *parent, value_type const &val) {
			//	надо ли проверять begin, end?
				node *new_node = new node(val);				
				node *tmp = parent->right;
				new_node->right = tmp;
				tmp->parent = new_node;
				new_node->parent = parent;
				parent->right = new_node;
				return (new_node);

			}

			// if inserted value greater than tree maximum value
			// end node has to be replaced
			node*	insert_val(value_type const &val)
			{
				if (_size == 0) {
					// head->set_value(val); // сработает?? -нет
					delete head;
					head = new_node(val);
					// head = new node(val);
					// head->right = end;
					// end->parent = head;
					// head->left = begin;
					// begin->parent = head;
					++_size;
					return head;
				}
				else {
				// node *new_node = new node(val);
				node *n = new_node(val);
				// node *max = max_node();
				// node *min = min_node();	// проверять минимальную ноду
				// if (_comp(max->value->first, val.first)) {
				// 	node *tmp = end;
				// 	max->right = new_node;
				// 	new_node->parent = max;
				// 	end = tmp;
				// 	new_node->right = end;
				// 	end->parent = new_node;
				// }
				// else if (_comp(val.first, min->value->first)) {
				// 	node *tmp = begin;
				// 	min->left = new_node;
				// 	new_node->parent = min;
				// 	begin = tmp;
				// 	new_node->left = begin;
				// 	begin->parent = new_node;
				// }
				// else
				insert_node(head, n);				
				++_size;
				return n;
				}
			}

			void	transplant(node* old_node, node* new_node)
			{
				node *tmp = old_node;
				if (old_node->parent == NULL)
					head = new_node;
				else if (old_node == old_node->parent->left)
					old_node->parent->left = new_node;
				else
					old_node->parent->right = new_node;
				if (new_node != NULL)
					new_node->parent = old_node->parent;
				delete tmp;	
			}

			void	delete_node(node* old_node) {
				if (old_node->left == NULL)
					transplant(old_node, old_node->right);
				else if (old_node->right == NULL)
					transplant(old_node, old_node->left);
				else {
					node *tmp = old_node->right->tree_min();
					if (tmp->parent != old_node) {
						transplant(tmp, tmp->right);
						tmp->right = old_node->right;
						tmp->right->parent = tmp;
					}
					transplant(old_node, tmp);
					tmp->left = old_node->left;
					tmp->left->parent = tmp;
				}
			}

			void	swap(Tree& other) {
				std::swap(this->head, other->head);
				std::swap(this->end, other->end);
				std::swap(this->size , other->size);
				std::swap(this->_alloc, other->_alloc);
				std::swap(this->_comp, other->_comp);
			}


	};	//	class Tree	

}	//	namespace ft

#endif

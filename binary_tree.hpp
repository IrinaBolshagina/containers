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

				node*	tree_min() { 
					node *n = this;
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

				node*	find_root() {
					node *n = this;
					while (n->parent->is_leaf == false) 
						n = n->parent;
					return n;
				}

				node*	successor() {
					node *n = this;
					if (n->right && n->right->is_leaf == false)
						return n->right->tree_min();
					node *y = n->parent;
					while (y && y->is_leaf == false && n == y->right) {
						n = y;
						y = y->parent;
					}
					return y;
				}

				node*	predecessor() {
					node *n = this;
					// if (n->is_leaf == true)
					// 	return n->left->tree_max();
					if (n->left->is_leaf == false || n->is_leaf == true)
						return n->left->tree_max();
					node *y = n->parent;
					while (y && y->is_leaf == false && n == y->left) {
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
			node			*begin;
			node			*end;
			key_compare		_comp;
			allocator_type	_alloc;
			size_type		_size;

		public:
		
			Tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : 
			_comp(comp), _alloc(alloc), _size(0), begin(NULL)  {
				end = new node(value_type());
				end->is_leaf = true;
				head = end->left;
			}

			Tree&	operator=( const Tree& other )
			{
				if (this == &other)
					return *this;
				if (other.empty())
					{
						this->clear();
						return *this;
					}
				this->clear();
				this->head = this->clone(other.head);
				this->end->left = this->head;
				this->head->parent = end;
				this->_size = other._size;
				this->_comp = other._comp;
				this->_alloc = other._alloc;
				return *this;
			}


		// 	Tree& operator=(const Tree&src) {
		// 	if (this == &src || src._size == 0)
		// 		return *this;
		// 	this->_alloc = src._alloc;
		// 	// this->_val_alloc = src._val_alloc;
		// 	this->_comp = src._comp;
		// 	// if (this->head == NULL) {
		// 	// 	end = new node(value_type());
		// 	// 	end->is_leaf = true;
		// 	// }
		// 	// else
		// 	if (this->head)
		// 		del_tree(head);
		// 	this->head = copy_node(src.head);
		// 	copy_child(this->head, src.head);
		// 	this->end->left = this->head;
		// 	this->head->parent = end;
		// 	this->_size = src._size;
		// 	return *this;
		// }

		// void	copy_child(node* my_node, node* other){
		// 	if (other->left) {
		// 		my_node->left = copy_node(other->left);
		// 		my_node->left->parent = my_node;
		// 		copy_child(my_node->left, other->left);
		// 	}
		// 	if (other->right) {
		// 		my_node->right = copy_node(other->right);
		// 		my_node->right->parent = my_node;
		// 		copy_child(my_node->right, other->right);
		// 	}
		// }


			// Tree&	operator= (const Tree& other) {
			// 	if (this == &other)
			// 		return *this;
			// 	// del_tree(head);
			// 	// this->head = copy_node(other.head);// скопировать head сначала, потом остальное дерево
			// 	this->head = clone(other.head);
			// 	// this->end = new node();
			// 	// this->head->parent = end;
			// 	// this->end->is_leaf = true;
			// 	// this->end->left = head;
			// 	this->end->left = this->head; // wtf??? this->end->left = this->head
			// 	this->head->parent = this->end;
			// 	this->_size = other._size;
			// 	this->_alloc = other._alloc;
			// 	this->_comp = other._comp;
			// 	return *this;
			// }

			~Tree() { del_tree(end); }

			void	del_tree(node *root) {
				if (root) {
					del_tree(root->left);
					del_tree(root->right);
					delete root;
				}
			}

			void	clear() {
				if (head) {
					del_tree(head);
					end->left = NULL;
					_size = 0;
				}
			}

			//	create new node with leafs
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
				res->is_leaf = src->is_leaf; 
				return res;
			}

			// node	*clone(node *src) {
			// 	node *res = copy_node(src);
			// 	if (src->left) { 
			// 		res->left = clone(src->left);
			// 		res->left->parent = res;
			// 	}
			// 	if (src->right) {
			// 		res->right = clone(src->right);
			// 		res->right->parent = res;
			// 	}
			// 	return res;
			// }

			node	*clone( node *src )
			{
				node *res = new node(*src->value);
				res->is_leaf = src->is_leaf;
				// node *res = copy_node(src);
					
				if (src->left->is_leaf) 
					// res->left = copy_node(src->left);
				{
					res->left = new node();
					res->left->parent = res;
					res->left->is_leaf = true;
				}
				else{
					res->left = this->clone(src->left);
					res->left->parent = res;
				}
				if (src->right->is_leaf) 
					// res->right = copy_node(src->right);
				{
					res->right = new node();
					res->right->is_leaf = true;
					res->left->parent = res;
				}
				else {
					res->right = this->clone(src->right);
					res->right->parent = res;
				}
				return res;
			}
			
			node*	head_node() const { return head; }

			node*	end_node() const { return end; }

			node*	begin_node() const { 
				if (_size == 0)
					return end;
				return min_node()->left; 
				}

			bool	empty() const { return _size == 0; }

			node*	search(node* root, const key_type& key) const {
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

			node*	max_node() const { return head->tree_max(); }

			node*	min_node() const { return head->tree_min(); }

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
				return new_node;
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
				return new_node;
			}

			node*	insert_val(value_type const &val)
			{
				node *n = new_node(val);
				if (_size == 0) {
					head = n;
					head->parent = end;
					end->left = head;
				}
				else
					insert_node(head, n);				
				++_size;
				return n;
			}

			void	transplant(node* old_node, node* new_node) {				
				node *tmp = old_node;
				if (old_node->parent->is_leaf == true) {
					head = new_node;
					head->parent = end;
					end->left = head;
					// return;
				}
				else if (old_node == old_node->parent->left)
					old_node->parent->left = new_node;
				else
					old_node->parent->right = new_node;
				new_node->parent = old_node->parent;
				// delete tmp;
			}

			void	delete_node(node* old_node) {
				node*	x;
				node*	y;
				node*	tmp = old_node;

				if (old_node->left->is_leaf == true) {
					x = old_node->left;
					transplant(old_node, old_node->right);
					delete x;
				}
				else if (old_node->right->is_leaf == true) {
					x = old_node->right;
					transplant(old_node, old_node->left);
					delete x;
				}
				else {
					y = old_node->right->tree_min();
					if (y->parent != old_node) {
						transplant(y, y->right);
						y->right = old_node->right;
						y->right->parent = y;
					}
					transplant(old_node, y);
					y->left = old_node->left;
					y->left->parent = y;
				}
				--_size;
				// if (x) delete x;
				delete tmp;
			}

			void swap(Tree &other) {
				ft::swap(this->head, other.head);
				ft::swap(this->end, other.end);
				ft::swap(this->begin, other.begin);	
				ft::swap(this->_size, other._size);
				ft::swap(this->_alloc, other._alloc);
				ft::swap(this->_comp, other._comp);
			}

			

			// 			node			*head;
			// node			*begin;
			// node			*end;
			// key_compare		_comp;
			// allocator_type	_alloc;
			// size_type		_size;

			// void	swap(Tree& other) {
			// 	ft::swap(this->head, other->head);
			// 	ft::swap(this->end, other->end);	
			// 	ft::swap(this->_size, other->_size);
			// 	ft::swap(this->_alloc, other->_alloc);
			// 	ft::swap(this->_comp, other->_comp);
			// }

	};	//	class Tree	

	template<class Value, class Compare, class Alloc>
	void swap(const  Tree<Value, Compare, Alloc>& lhs, const  Tree<Value, Compare, Alloc>& rhs)
		{ lhs.swap(rhs); }
	
	template <class Value, class Compare, class Alloc>
	bool operator<(
			const Tree<Value, Compare, Alloc>& lhs,
			const Tree<Value, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Value, class Compare, class Alloc>
	bool operator>(
			const Tree<Value, Compare, Alloc>& lhs,
			const Tree<Value, Compare, Alloc>& rhs)
	{
		return (lhs < rhs);
	}


	template<class Value, class Compare, class Alloc>
	bool operator==(
			const Tree<Value, Compare, Alloc>& lhs,
			const Tree<Value, Compare, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

}	//	namespace ft





#endif

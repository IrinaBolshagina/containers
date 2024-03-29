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

				node() : value(NULL), left(NULL), right(NULL), parent(NULL), is_leaf(false) {}

				~node() {}

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
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef ft::pair <const key_type, mapped_type>				value_type;
			typedef Allocator											allocator_type;
			typedef Compare												key_compare;
			typedef typename allocator_type::size_type					size_type;
			typedef node <value_type, allocator_type>					node;
			typedef typename Allocator::template rebind <node>::other	node_allocator;
		
		private:
			node			*head;
			node			*begin;
			node			*end;
			key_compare		_comp;
			allocator_type	_alloc;
			node_allocator	_node_alloc;
			size_type		_size;

		public:
		
			Tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : 
			begin(NULL), _comp(comp), _alloc(alloc), _size(0)  {
				end = new_node();
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

			~Tree() { del_tree(end); }

			node*	new_node(const value_type& val = value_type()) {
				// node* n = new node(val);
				node* n = _node_alloc.allocate(1);
				_node_alloc.construct(n, node());
				n->value = _alloc.allocate(1);
				_alloc.construct(n->value, value_type(val));
				return n;
			}

			void	del_node(node *n) {
				_alloc.destroy(n->value);
				_alloc.deallocate(n->value, 1);
				_node_alloc.deallocate(n, 1);
			}

			void	del_tree(node *root) {
				if (root) {
					del_tree(root->left);
					del_tree(root->right);
					del_node(root);
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
			node* new_node_leafs(const value_type& val) {
				node *n = new_node(val);
				n->left = new_node(); 		//	left leaf
				n->left->is_leaf = true;
				n->left->parent = n;
				n->right = new_node();		//	right leaf
				n->right->is_leaf = true;
				n->right->parent = n;
				return n;
			}

			node	*copy_node(node *src) {
				node *res = new_node(*src->value);
				res->is_leaf = src->is_leaf; 
				return res;
			}

			node	*clone( node *src )
			{
				node *res = new_node(*src->value);
				res->is_leaf = src->is_leaf;
				// node *res = copy_node(src);
					
				if (src->left->is_leaf) 
					// res->left = copy_node(src->left);
				{
					res->left = new_node();
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
					res->right = new_node();
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

			node*	insert_node(node* root, node* n) {
				if (_comp(n->value->first, root->value->first)) {
					if (root->left->is_leaf == false)
						return (insert_node(root->left, n));
					del_node(root->left); // delete leaf
					root->left = n;
				}
				else {
					if (root->right->is_leaf == false)
						return (insert_node(root->right, n));
					del_node(root->right);
					root->right = n;
				}
				n->parent = root;
				return n;
			}

			//	inserts right child to parent node
			node*	insert_val(node *parent, value_type const &val) {
			//	надо ли проверять begin, end?
				node *n = new_node(val);				
				node *tmp = parent->right;
				n->right = tmp;
				tmp->parent = n;
				n->parent = parent;
				parent->right = n;
				return n;
			}

			node*	insert_val(value_type const &val)
			{
				node *n = new_node_leafs(val);
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

			void	transplant(node* old_node, node* n) {				
				node*	tmp = old_node;
				if (old_node->parent->is_leaf == true) {
					head = n;
					head->parent = end;
					end->left = head;
				}
				else if (old_node == old_node->parent->left)
					old_node->parent->left = n;
				else
					old_node->parent->right = n;
				n->parent = old_node->parent;
				del_node(tmp);
			}

			void	delete_node(node* old_node) {
				node*	x;
				node*	y;
				// node*	tmp = old_node;

				if (old_node->left->is_leaf == true) {
					x = old_node->left;
					transplant(old_node, old_node->right);
					del_node(x);
				}
				else if (old_node->right->is_leaf == true) {
					x = old_node->right;
					transplant(old_node, old_node->left);
					del_node(x);
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
				// del_node(tmp);
			}

			void swap(Tree &other) {
				ft::swap(this->head, other.head);
				ft::swap(this->end, other.end);
				ft::swap(this->begin, other.begin);	
				ft::swap(this->_size, other._size);
				ft::swap(this->_alloc, other._alloc);
				ft::swap(this->_comp, other._comp);
			}

	};	//	class Tree	

	template<class Value, class Compare, class Alloc>
	void swap(const  Tree<Value, Compare, Alloc>& lhs, const  Tree<Value, Compare, Alloc>& rhs)
		{ lhs.swap(rhs); }
	
	template <class Value, class Compare, class Alloc>
	bool operator < (const Tree<Value, Compare, Alloc>& lhs,
			const Tree<Value, Compare, Alloc>& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

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

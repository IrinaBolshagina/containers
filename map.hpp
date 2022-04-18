#ifndef MAP_HPP
# define MAP_HPP

#include "utility.hpp"
#include "map_iterator.hpp"
#include "binary_tree.hpp"

namespace ft {

	template  <	class Key, class T,														
				class Compare = std::less<Key>,									
				class Allocator = std::allocator<ft::pair<const Key, T> > > 	
	class map {

		public:

		//	Member types
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair <const key_type, mapped_type>		value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef Compare										key_compare;
			typedef node <value_type, allocator_type>			node;
			typedef Tree <key_type, mapped_type, 
						key_compare, allocator_type>			tree_type;
			typedef BidirectionalIterator <value_type, allocator_type>			iterator;
			typedef	BidirectionalIterator <const value_type, allocator_type>	const_iterator;
			// reverse_iterator;
			// const_reverse_iterator;

		private:

			class value_compare {
				private:
					Compare		_comp;
				protected:
				//	Constructor
					value_compare(Compare c) : _comp(c) {}
				public:
				//	Compares two values of type value_type
					bool operator() (const value_type& lhs, const value_type& rhs) const 
					{ return _comp(lhs.first, rhs.first); }
			};

		private:
			allocator_type		_alloc;
			tree_type			_tree;
			key_compare			_comp;

		public:

		//	default constructor
			explicit map (const key_compare& comp = key_compare(), 
				const allocator_type& alloc = allocator_type()) {}

		//	range constructor
			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
       			const allocator_type& alloc = allocator_type()) {}

		//	copy constructor
			map (const map& other) {}

		//	assignment operator
			map& operator= (const map& other) {}

		//	destructor
			~map() {}

		//	Allocator
			allocator_type get_allocator() const;

		//	Iterators
			iterator begin() { 
				if (size() < 2)
					return iterator(_tree.head_node());
				else
					return iterator(_tree.min_node());
			}
			iterator end() { 
				if (_tree.isEmpty())
					return iterator(_tree.head_node());
				else
					return iterator(_tree.end_node());
			}
			// const_iterator begin() const;
			// const_iterator end() const;
			// reverse_iterator rbegin();
			// reverse_iterator rend();
			// const_reverse_iterator rbegin() const;
			// const_reverse_iterator rend() const;
		
		// Capacity
			bool empty() const { return _tree.isEmpty(); }
			size_type size() const { return _tree.size(); }
			size_type max_size() const { return _alloc.max_size(); }

		//	Element access
			mapped_type& operator[] (const key_type& k);
			T& at(const Key& key);
			const T& at(const Key& key) const;

		//	Modifiers

	private: 

		// void insert(node *&root, node *new_node)
		// 	{
		// 		if (root == NULL)
		// 			root = new_node;
		// 		else
		// 		{
		// 			if (_comp(new_node->value->first, root->value->first))
		// 				insert(root->left, new_node);

		// 			else 
		// 				insert(root->right, new_node);
		// 		}
		// 	}

		// node *insert_val(value_type const &val)
		// {
		// 	node *new_node = new node(val);
		// 	if (_tree.head == _tree.root)
		// 		_tree.root = new_node;
		// 	else {
		// 		node *max = _tree.max_node();
		// 		if (_comp(max->value->first, val.first)) {
		// 			delete(_tree.end);
		// 			node *max = _tree.max_node();
		// 			max->right = new_node;
		// 			_tree.end = new node();
		// 			new_node->right = _tree.end;
		// 		}
		// 		else
		// 			insert (_tree.root, new_node);
		// 	}
		// 	// ++_size;

		// 	return new_node;
		// }

		public:

			//	Inserts single element
			pair<iterator,bool> insert (const value_type& val) { 
				// проверять повторяется ли ключ
				if (!_tree.find(val)) 
				// if(find(val->first) == end()) 
					return ft::make_pair(iterator(_tree.insert_val(val)), true);
				else 
					return ft::make_pair(iterator(_tree.find(val)), false);
			}


			//	With a hint
			// iterator insert (iterator position, const value_type& val);

			//	Inserts range 	
			// template <class InputIterator>
			// void insert (InputIterator first, InputIterator last);

			void swap (map& x);
			void clear();

			//	Observers
			key_compare key_comp(Compare c) const;
			// value_compare value_comp() const;
			value_compare value_comp() const { return value_compare(_comp); }

			//	Operations
			iterator find (const key_type& k) {
				return _tree.find(make_pair(k, mapped_type()));
			}
			const_iterator find (const key_type& k) const {return _tree.find(make_pair(k, mapped_type()));}
			size_type count (const key_type& k) const;
			iterator lower_bound (const key_type& k);
			const_iterator lower_bound (const key_type& k) const;
			iterator upper_bound (const key_type& k);
			const_iterator upper_bound (const key_type& k) const;
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			pair<iterator,iterator> equal_range (const key_type& k);



	};	//	class map

	//	Operators

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs );


}	//	namespace ft

#endif
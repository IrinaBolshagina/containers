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
					Compare	_comp;
				protected:
				//	Constructor
					value_compare(Compare c) : _comp(c) {}
				public:
				//	Compares two values of type value_type
					bool operator() (const value_type& lhs, const value_type& rhs) const 
					{ return _comp(lhs.first, rhs.first); }
			};

		// private:
		public:
			allocator_type		_alloc;
			key_compare			_comp;
			tree_type			_tree;

		public:

		// map() {}

		//	default constructor
			explicit map (const key_compare& comp = key_compare(), 
				const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp), _tree(tree_type(comp, alloc)) {}

		//	range constructor
			template <class InputIterator>
  			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
       			const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp), _tree(tree_type(comp, alloc)) { 
					insert(first, last);
			}

		//	copy constructor
			map (const map& other) {
				*this = other;
			}



		//	assignment operator
			map&	operator= (const map& other) {
				if (this != &other) {
					_alloc = other._alloc;
					_comp = other._comp;
					// if (!this->_tree.empty())
					// 	clear();
					_tree = other._tree;	
					
					// iterator first = other.begin();
					// iterator last = other.end();
					// for(; first != last; ++first)
					// 	_tree.insert_val(*first);
				}
				return *this;
			}

		//	destructor
			~map() {}

		//	Allocator
			allocator_type	get_allocator() const { return _alloc; }

		//	Iterators
			iterator	begin() { 
				if (_tree.empty())
					return iterator(_tree.end_node());
				if (size() == 1)
					return iterator(_tree.head_node());
				else
					return iterator(_tree.min_node());
			}

			iterator	end() { 
				// if (_tree.empty())
				// 	return iterator(_tree.head_node());
				return iterator(_tree.end_node());
			}
			// const_iterator begin() const { 
			// 	if (size() < 2)
			// 		return const_iterator(_tree.head_node());
			// 	else
			// 		return const_iterator(_tree.min_node());
			// }
			// const_iterator end() const { 
			// 	if (_tree.empty())
			// 		return const_iterator(_tree.head_node());
			// 	else
			// 		return const_iterator(_tree.end_node());
			// }
			// reverse_iterator rbegin();
			// reverse_iterator rend();
			// const_reverse_iterator rbegin() const;
			// const_reverse_iterator rend() const;
		
		// Capacity
			bool		empty() const { return _tree.empty(); }
			
			size_type	size() const { return _tree.size(); }
			
			size_type	max_size() const { return _alloc.max_size(); }

		//	Element access
			mapped_type&	operator[] (const key_type& key) {
				return (*((insert(ft::make_pair(key, mapped_type()))).first)).second;
			}

			mapped_type&	at(const key_type& key) {
				if (!_tree.search(ft::make_pair(key, mapped_type())))
					throw std::out_of_range("key is out of range");
				else
					return (*this)[key];
			}

			const mapped_type&	at(const key_type& key) const {
				if (!_tree.search(ft::make_pair(key, mapped_type())))
					throw std::out_of_range("key is out of range");
				else
					return (*this)[key];
			}
			

		//	Modifiers
		public:

			//	Inserts single element
			pair<iterator,bool>	insert (const value_type& val) { 
				// check if map already contains value with this key
				if (!_tree.search(val)) 
					return ft::make_pair(iterator(_tree.insert_val(val)), true);
				else 
					return ft::make_pair(iterator(_tree.search(val)), false);
			}


			//	With a hint - inserts after the position
			//	if position points to the element that will precede the inserted element
			iterator	insert (iterator hint, const value_type& val) {
				// if ((*position).first + 1 == val.first)
				// 	return(iterator(_tree.insert_val(val)));
				node* n = _tree.search(val);
				if (n) 
					return (iterator(n));
				n = hint.node();
				if (hint != end() && _comp((*hint).first, val.first) && _comp(val.first, (*(++hint)).first)) // убрать итерацию хинта
					return(iterator(_tree.insert_val(n, val)));
				return(iterator(_tree.insert_val(val)));
			}

			//	Inserts range 	
			template <class InputIterator>
			void	insert (InputIterator first, InputIterator last) {
				for(; first != last; ++first)
					_tree.insert_val(*first);
			}

			// template <class InputIterator>
			// void insert(InputIterator first, InputIterator last)
			// {
			// 	for ( ; first != last; ++first)
			// 		insert(ft::make_pair(first->first, first->second));
			// }

			void erase(iterator pos) {
				_tree.delete_node(pos.node());
			}

			size_type	erase(const key_type& key) {
				node *res = _tree.search(ft::make_pair(key, mapped_type()));
				if (!res)
					return 0;
				_tree.delete_node(res);
				return 1;

			}

     		void	erase(iterator first, iterator last) {
				while (first != last)
 					erase(first++);
			}

			// void	erase( iterator first, iterator last )
			// {
			// 	while (first != last)
			// 		this->_tree.delete_node((first++).node());
			// }

			void	clear() {
				_tree.clear();
			}

			void	swap(map& other) {
				std::swap(this->_comp, other._comp);
				std::swap(this->_alloc, other._alloc);
				// std::swap(this->_tree, other._tree);
				_tree.swap(other._tree);
			}

			//	Observers
			key_compare	key_comp() const { return _comp; }

			value_compare	value_comp() const { return value_compare(_comp); }

			//	Operations
			iterator	find (const key_type& k) {
				node* res = _tree.search(ft::make_pair(k, mapped_type()));
				if (res) 
					return iterator(res);
				else 
					return end();
				}
			
			//	Because all elements in a map container are unique, 
			//	the function can only return 1 (if the element is found) or zero
			size_type	count (const key_type& k) const {
				if (_tree.search(make_pair(k, mapped_type())))
					return 1;
				else
					return 0;
			}

			iterator	lower_bound (const key_type& k) {
				for (iterator it = begin(); it != end(); ++it)
					if(comp(k, (*it).first))
						return it;
				return NULL;
			}
			const_iterator	lower_bound (const key_type& k) const;
			iterator	upper_bound (const key_type& k);
			const_iterator	upper_bound (const key_type& k) const;
			pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
			pair<iterator,iterator>	equal_range (const key_type& k);


			// friend bool	operator==(const map &lhs, const map &rhs) {
			// 	iterator	l_begin = lhs.begin();
			// 	iterator	l_end = lhs.end();
			// 	iterator	r_begin = rhs.begin();
			// 	iterator	r_end = rhs.end();
			// 	while (l_begin != l_end && r_begin != r_end) {
			// 		if (l_begin->second != r_begin->second)
			// 			return false;
			// 		l_begin++;
			// 		r_begin++;
			// 	}
			// 	if (l_begin != l_end || r_begin != r_end)
			// 		return false;
			// 	return true;
			// }


	};	//	class map

	//	Operators

	template< class Key, class T, class Compare, class Allocator >
	bool operator==	(const ft::map<Key,T,Compare,Allocator>& lhs, 
					const ft::map<Key,T,Compare,Allocator>& rhs ) {
		
		BidirectionalIterator <ft::pair <const Key, T>, Allocator>	l_begin = lhs.begin();
		BidirectionalIterator <ft::pair <const Key, T>, Allocator>	l_end = lhs.end();
		BidirectionalIterator <ft::pair <const Key, T>, Allocator>	r_begin = rhs.begin();
		BidirectionalIterator <ft::pair <const Key, T>, Allocator>	r_end = rhs.end();
		
		if (lhs.size() != rhs.size())
			return false;
		while (l_begin != l_end && r_begin != r_end) {
			if (l_begin->second != r_begin->second)
				return false;
			++l_begin;
			++r_begin;
		}
		if (l_begin != l_end || r_begin != r_end)
			return false;
		return true;
	}

	// template< class Key, class T, class Compare, class Alloc >
	// bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
	// 				const ft::map<Key,T,Compare,Alloc>& rhs );

	// template< class Key, class T, class Compare, class Alloc >
	// bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
	// 				const ft::map<Key,T,Compare,Alloc>& rhs );

	// template< class Key, class T, class Compare, class Alloc >
	// bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
	// 				const ft::map<Key,T,Compare,Alloc>& rhs );

	// template< class Key, class T, class Compare, class Alloc >
	// bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
	// 				const ft::map<Key,T,Compare,Alloc>& rhs );

	// template< class Key, class T, class Compare, class Alloc >
	// bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
	// 				const ft::map<Key,T,Compare,Alloc>& rhs );


}	//	namespace ft

#endif
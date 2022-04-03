#ifndef MAP_HPP
# define MAP_HPP

#include "utility.hpp"
#include "map_iterator.hpp"
#include "binary_tree.hpp"

namespace ft {

	template  <	class Key,														
				class T,														
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
			typedef Tree <value_type>							tree_type;
			typedef BidirectionalIterator <value_type>			iterator;
			// const_iterator;
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

		//	Iterators
			iterator begin();
			iterator end();
			// const_iterator begin() const;
			// const_iterator end() const;
			// reverse_iterator rbegin();
			// reverse_iterator rend();
			// const_reverse_iterator rbegin() const;
			// const_reverse_iterator rend() const;
		
		// Capacity
			bool empty() const { return _tree.isEmpty(); }
			size_type size() const { return _tree.size(); }
			size_type max_size() const;


	};	//	class map





}	//	namespace ft

#endif
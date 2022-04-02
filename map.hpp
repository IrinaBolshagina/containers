#ifndef MAP_HPP
# define MAP_HPP

#include "utility.hpp"
#include "map_iterator.hpp"

namespace ft {

	template <class T>
	class node {
		public:
			typedef T		value_type;
	};

	template  <	class Key,														// map::key_type
				class T,														// map::mapped_type
				class Compare = std::less<Key>,									// map::key_compare
				class Allocator = std::allocator<ft::pair<const Key, T> > > 	// map::allocator_type
	class map {

		public:

		//	Member types
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair <const key_type, mapped_type>			value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;

			typedef BidirectionalIterator <value_type>			iterator;
			// reverse_iterator;
			// const_iterator;
			// const_reverse_iterator;

		//	Constructors





	};	//	class map





}	//	namespace ft

#endif
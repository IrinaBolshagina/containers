#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iterator>
#include "utility.hpp"
#include "binary_tree.hpp"

namespace ft {

	template < typename T, class Allocator = std::allocator<T> >
	class BidirectionalIterator {

		public:
			typedef Allocator											allocator_type;
			typedef typename ft::iterator_traits<T*>::value_type		value_type;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef std::bidirectional_iterator_tag 					iterator_category;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::reference			reference;
			typedef pointer												iterator_type;
			typedef node <value_type, allocator_type> *					node_pointer;
			
		private:
			node_pointer	_node;
			bool			_is_end;

		public:

		//	constructors and staff
			BidirectionalIterator(node_pointer node = 0) : _node(node) {}
			BidirectionalIterator(const BidirectionalIterator<value_type, allocator_type> &other) { *this = other; }
			virtual ~BidirectionalIterator() {}
			BidirectionalIterator &operator=( const BidirectionalIterator<value_type, allocator_type> &other) {
				if(this != &other)
					this->_node = other._node;
				return *this;
			}
		
		//	member functions
			node_pointer				node() const { return _node; }
			
		//	operators overload
			reference					operator*() const { return *(_node->value); }
			pointer						operator->() const { return _node->value; }

			// BidirectionalIterator&		operator++() { ++_node; return *this; }
			// BidirectionalIterator&		operator++(int) { return BidirectionalIterator(_node++); }
			// BidirectionalIterator&		operator--() { --_node; return *this; }
			// BidirectionalIterator&		operator--(int) { return BidirectionalIterator(_node--); }
			
			// friend bool	operator==(const BidirectionalIterator & lhs, const BidirectionalIterator & rhs, ) const 
			// 	{ return (_node == other._node); }
			// friend bool	operator!=(const BidirectionalIterator & lhs, const BidirectionalIterator & rhs, ) const
			// 	{ return (_node != other._node); }

	};	//	class BidirectionalIterator

}	//	namespace ft


#endif
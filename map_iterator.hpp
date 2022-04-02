#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iterator>
#include "utility.hpp"

namespace ft {

	template <typename T> class BidirectionalIterator {

		public:
			typedef typename iterator_traits<T*>::value_type			value_type;
			typedef typename iterator_traits<T*>::difference_type		difference_type;
			typedef typename iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename iterator_traits<T*>::pointer				pointer;
			typedef typename iterator_traits<T*>::reference				reference;
			typedef pointer												iterator_type;
			
		private:
			pointer	_node;

		public:

		//	constructors and staff
			BidirectionalIterator(pointer node = 0) : _node(node) {}
			BidirectionalIterator(const BidirectionalIterator &other) { *this = other; }
			virtual ~BidirectionalIterator() {}
			BidirectionalIterator &operator=( const BidirectionalIterator &other) {
				if(this != &other)
					this->_node = other._node;
				return *this;
			}
		
		//	member functions
			pointer		getPointer() const { return _node; }
			
		//	operators overload
			reference					operator*() const { return *_node; }
			pointer						operator->() const { return _node; }
			reference					operator[](const difference_type &n) const { return _node[n]; }

			// BidirectionalIterator&		operator++() { ++_node; return *this; }
			// BidirectionalIterator&		operator++(int) { return BidirectionalIterator(_node++); }
			// BidirectionalIterator&		operator--() { --_node; return *this; }
			// BidirectionalIterator&		operator--(int) { return BidirectionalIterator(_node--); }
			bool						operator==(const BidirectionalIterator & other) const { return (_node == other._node); }
			bool 						operator!=(const BidirectionalIterator & other) const { return (_node != other._node); }

	};	//	class BidirectionalIterator

}	//	namespace ft


#endif
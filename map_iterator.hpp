#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iterator>
#include "utility.hpp"
#include "binary_tree.hpp"

namespace ft {

	template < class Value, class Allocator = std::allocator<Value> >
	class BidirectionalIterator {

		public:
			typedef Value													value_type;
			typedef Allocator												allocator_type;
			typedef typename ft::iterator_traits<Value*>::difference_type	difference_type;
			typedef std::bidirectional_iterator_tag 						iterator_category;
			typedef typename ft::iterator_traits<Value*>::pointer			pointer;
			typedef typename ft::iterator_traits<Value*>::reference			reference;
			typedef pointer													iterator_type;
			typedef node <value_type, allocator_type> *						node_pointer;
			
		private:
			node_pointer	_node;

		public:

		//	constructors and staff
			BidirectionalIterator(node_pointer node = 0) : _node(node) {}
			BidirectionalIterator(const BidirectionalIterator<value_type, allocator_type> &other) { *this = other; }
			virtual ~BidirectionalIterator() {}
			BidirectionalIterator &operator=(const BidirectionalIterator<value_type, allocator_type> &other) {
				if(this != &other)
					this->_node = other._node;
				return *this;
			}
		
		//	member functions
			node_pointer				node() const { return _node; }
			
		//	operators overload
			reference					operator*() const { return *(_node->value); }
			pointer						operator->() const { return _node->value; }

			BidirectionalIterator& operator++() {
				_node = _node->successor();
				return *this;
			}

			BidirectionalIterator		operator++(int) {
				BidirectionalIterator tmp(_node);
				++(*this);
				return tmp;
            }
			
			BidirectionalIterator&		operator--() { 
				_node = _node->predecessor();
				return *this;
			}
			
			BidirectionalIterator		operator--(int) { 
				BidirectionalIterator tmp(_node);
				--(*this);
				return tmp;
			}
			
			bool operator==(const BidirectionalIterator &other) { return this->_node == other._node; }
			bool operator!=(const BidirectionalIterator &other) { return this->_node != other._node; }

// remove!
			void print_end() { std::cout << _node->is_end << "\n"; }
			node_pointer right() const { return _node->right; }
// remove!

	};	//	class BidirectionalIterator

}	//	namespace ft


#endif
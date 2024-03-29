#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iterator>
#include "utility.hpp"
#include "binary_tree.hpp"

namespace ft {

	template < class Value, class Allocator = std::allocator<Value> >
	class BidirectionalIterator {

		public:
			typedef typename ft::iterator_traits<Value*>::value_type		value_type;
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
			BidirectionalIterator(const BidirectionalIterator<typename std::remove_const<value_type>::type, allocator_type> & other) : _node(other.node()) {}
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

			// BidirectionalIterator& operator++()
			// {
			// 	if (_node->right && _node->right->is_leaf == false)
			// 		_node = _node->right->tree_min();
			// 	else
			// 	{
			// 		node_pointer y = _node->parent;
			// 		while (y && y->is_leaf == false && _node == y->right)
			// 		{
			// 			_node = y;
			// 			y = y->parent;
			// 		}
			// 		_node = y;
			// 	}
			// 	return *this;
			// }

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


	};	//	class BidirectionalIterator

}	//	namespace ft


#endif
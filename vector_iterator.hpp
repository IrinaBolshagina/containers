#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include <iterator>
#include "utility.hpp"

namespace ft {

	template <typename T> class RandomAccessIterator {

		public:
			typedef typename ft::iterator_traits<T*>::value_type			value_type;
			typedef typename ft::iterator_traits<T*>::difference_type		difference_type;
			typedef typename ft::iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename ft::iterator_traits<T*>::pointer				pointer;
			typedef typename ft::iterator_traits<T*>::reference				reference;
			typedef pointer													iterator_type;

		private:
			pointer	_ptr;

		public:

		//	constructors and staff
			RandomAccessIterator(pointer ptr = 0) : _ptr(ptr) {}
			
			RandomAccessIterator(const RandomAccessIterator<typename std::remove_const<value_type>::type > & src) : _ptr(&(*src)) {}

			virtual ~RandomAccessIterator() {}

			// RandomAccessIterator<value_type> & operator=(RandomAccessIterator<typename remove_const<value_type>::type > const & src) {
			// 	_ptr = &(*src);
			// 	return *this;
			// }

			RandomAccessIterator &operator=( const RandomAccessIterator &other) {
				if(this != &other)
					this->_ptr = other._ptr;
				return *this;
			}

		//	member functions
			pointer		getPointer() const { return _ptr; }

		//	operators overload
			reference					operator*() const { return *_ptr; }
			pointer						operator->() const { return _ptr; }
			reference					operator[](const difference_type &n) const { return _ptr[n]; }

			RandomAccessIterator&		operator++() { ++_ptr; return *this; }
			RandomAccessIterator		operator++(int) { return RandomAccessIterator(_ptr++); } // пофиксить
			RandomAccessIterator&		operator--() { --_ptr; return *this; }
			RandomAccessIterator		operator--(int) { return RandomAccessIterator(_ptr--); }
			RandomAccessIterator&		operator+=(const difference_type &n) { _ptr += n; return *this; }
			RandomAccessIterator&		operator-=(const difference_type &n) { _ptr -= n; return *this; }
			RandomAccessIterator		operator+(const difference_type &n) { return RandomAccessIterator(_ptr + n); }
			RandomAccessIterator		operator-(const difference_type &n) { return RandomAccessIterator(_ptr - n); }

			friend bool					operator==(const RandomAccessIterator &lhs, const RandomAccessIterator &rhs) { return (lhs._ptr == rhs._ptr); }
			friend bool 				operator!=(const RandomAccessIterator &lhs, const RandomAccessIterator &rhs) { return (lhs._ptr != rhs._ptr); }
			friend bool					operator<(const RandomAccessIterator &lhs, const RandomAccessIterator &rhs)  { return (lhs._ptr < rhs._ptr); }
			friend bool					operator>(const RandomAccessIterator &lhs, const RandomAccessIterator &rhs)  { return (lhs._ptr > rhs._ptr); }
			friend bool					operator<=(const RandomAccessIterator &lhs, const RandomAccessIterator &rhs)  { return (lhs._ptr <= rhs._ptr); }
			friend bool					operator>=(const RandomAccessIterator &lhs, const RandomAccessIterator &rhs)  { return (lhs._ptr >= rhs._ptr); }

			friend RandomAccessIterator	operator+(const difference_type &n, const RandomAccessIterator & other) { return other + n; }
			friend RandomAccessIterator	operator-(const difference_type &n, const RandomAccessIterator & other) { return other - n; }
			friend difference_type		operator-(const RandomAccessIterator& lhs, RandomAccessIterator& rhs) { return lhs._ptr - rhs._ptr; }
			difference_type				operator-(RandomAccessIterator const &obj) const { return _ptr - obj._ptr; }
	};	//	class RandomAccessIterator


}	//	namespace ft


#endif

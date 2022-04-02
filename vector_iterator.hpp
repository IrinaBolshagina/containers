#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include <iterator>
#include "utility.hpp"

namespace ft {

	template <typename T> class RandomAccessIterator {

		public:
			typedef typename iterator_traits<T*>::value_type			value_type;
			typedef typename iterator_traits<T*>::difference_type		difference_type;
			typedef typename iterator_traits<T*>::iterator_category		iterator_category;
			typedef typename iterator_traits<T*>::pointer				pointer;
			typedef typename iterator_traits<T*>::reference				reference;
			typedef pointer												iterator_type;

		private:
			pointer	_ptr;

		public:

		//	constructors and staff
			RandomAccessIterator(pointer ptr = 0) : _ptr(ptr) {}
			RandomAccessIterator(const RandomAccessIterator &other) { *this = other; }
			virtual ~RandomAccessIterator() {}
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
			RandomAccessIterator&		operator++(int) { return RandomAccessIterator(_ptr++); }
			RandomAccessIterator&		operator--() { --_ptr; return *this; }
			RandomAccessIterator&		operator--(int) { return RandomAccessIterator(_ptr--); }
			RandomAccessIterator&		operator+=(const difference_type &n) { _ptr += n; return *this; }
			RandomAccessIterator&		operator-=(const difference_type &n) { _ptr -= n; return *this; }
			RandomAccessIterator		operator+(const difference_type &n) { return RandomAccessIterator(_ptr + n); }
			RandomAccessIterator		operator-(const difference_type &n) { return RandomAccessIterator(_ptr - n); }

			bool						operator==(const RandomAccessIterator & other) const { return (_ptr == other._ptr); }
			bool 						operator!=(const RandomAccessIterator & other) const { return (_ptr != other._ptr); }
			bool						operator<(const RandomAccessIterator & other) const { return (_ptr < other._ptr); }
			bool						operator>(const RandomAccessIterator & other) const { return (_ptr > other._ptr); }
			bool						operator<=(const RandomAccessIterator & other) const { return (_ptr <= other._ptr); }
			bool						operator>=(const RandomAccessIterator & other) const { return (_ptr >= other._ptr); }

			friend RandomAccessIterator	operator+(const difference_type &n, const RandomAccessIterator & other) { return other + n; }
			friend RandomAccessIterator	operator-(const difference_type &n, const RandomAccessIterator & other) { return other - n; }
			friend difference_type		operator-(const RandomAccessIterator& lhs, RandomAccessIterator& rhs) { return lhs._ptr - rhs._ptr; }

	};	//	class RandomAccessIterator
	

	//	reverse iterator

	template<class Iter> struct reverse_iterator
	{
		typedef Iter										iterator_type;
		typedef typename iterator_type::value_type			value_type;
		typedef typename iterator_type::pointer				pointer;
		typedef typename iterator_type::reference			reference;
		typedef typename iterator_type::difference_type		difference_type;
		typedef typename iterator_type::iterator_category	iterator_category;
	};


}	//	namespace ft


#endif

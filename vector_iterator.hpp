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


	// //	reverse iterator

		// 	template <typename Iter> class reverse_iterator {

		// public:
		// typedef Iter										iterator_type;
		// typedef typename iterator_type::value_type			value_type;
		// typedef typename iterator_type::pointer				pointer;
		// typedef typename iterator_type::reference			reference;
		// typedef typename iterator_type::difference_type		difference_type;
		// typedef typename iterator_type::iterator_category	iterator_category;

		// private:
		// 	iterator_type iterator;
		// 	pointer	_ptr;

		// public:

		// //	constructors and staff
		// 	reverse_iterator(pointer ptr = 0) : _ptr(ptr) {}
		// 	reverse_iterator(const reverse_iterator &other) { *this = other; }
		// 	virtual ~reverse_iterator() {}
		// 	reverse_iterator &operator=( const reverse_iterator &other) {
		// 		if(this != &other)
		// 			this->_ptr = other._ptr;
		// 		return *this;
		// 	}

		// //	member functions
		// 	pointer		getPointer() const { return _ptr; }

		// 	iterator_type base() const { return iterator; }

		// //	operators overload
		// 	reference					operator*() const { return *_ptr; }
		// 	pointer						operator->() const { return _ptr; }
		// 	reference					operator[](const difference_type &n) const { return _ptr[n]; }

		// 	reverse_iterator&		operator++() { --_ptr; return *this; }
		// 	reverse_iterator&		operator++(int) { return reverse_iterator(_ptr--); }
		// 	reverse_iterator&		operator--() { ++_ptr; return *this; }
		// 	reverse_iterator&		operator--(int) { return reverse_iterator(_ptr++); }
		// 	reverse_iterator&		operator+=(const difference_type &n) { _ptr -= n; return *this; }
		// 	reverse_iterator&		operator-=(const difference_type &n) { _ptr += n; return *this; }
		// 	reverse_iterator		operator+(const difference_type &n) { return reverse_iterator(_ptr + n); }
		// 	reverse_iterator		operator-(const difference_type &n) { return reverse_iterator(_ptr - n); }

		// 	bool						operator==(const reverse_iterator & other) const { return (_ptr == other._ptr); }
		// 	bool 						operator!=(const reverse_iterator & other) const { return (_ptr != other._ptr); }
		// 	bool						operator<(const reverse_iterator & other) const { return (_ptr < other._ptr); }
		// 	bool						operator>(const reverse_iterator & other) const { return (_ptr > other._ptr); }
		// 	bool						operator<=(const reverse_iterator & other) const { return (_ptr <= other._ptr); }
		// 	bool						operator>=(const reverse_iterator & other) const { return (_ptr >= other._ptr); }

		// 	friend reverse_iterator	operator+(const difference_type &n, const reverse_iterator & other) { return other + n; }
		// 	friend reverse_iterator	operator-(const difference_type &n, const reverse_iterator & other) { return other - n; }
		// 	friend difference_type		operator-(const reverse_iterator& lhs, reverse_iterator& rhs) { return lhs._ptr - rhs._ptr; }
		// 	};

	// 	template <class Iterator>
	// 	class reverse_iterator {

	// 	public:
	// 	typedef Iterator									iterator_type;
	// 	typedef typename iterator_type::value_type			value_type;
	// 	typedef typename iterator_type::pointer				pointer;
	// 	typedef typename iterator_type::reference			reference;
	// 	typedef typename iterator_type::difference_type		difference_type;
	// 	typedef typename iterator_type::iterator_category	iterator_category;

	// 	private:
	// 		iterator_type _iterator;

	// 	public:
	// 	//	constructors and staff
	// 		reverse_iterator() : _iterator() {}

	// 		explicit reverse_iterator (iterator_type it) : _iterator(it) {}

	// 		template <class Iter> 
	// 			reverse_iterator (const reverse_iterator<Iter> &other) 
	// 			{ this->_iterator = other->_iterator; }

	// 		virtual ~reverse_iterator() {}

	// 		reverse_iterator &operator=( const reverse_iterator &other) {
	// 			if(this != &other)
	// 				this->_iterator = other._iterator;
	// 			return *this;
	// 		}

	// 	//	member functions
	// 		iterator_type	base() const { return _iterator; }

	// 	//	operators overload
	// 		reference	operator*() const { 
	// 			iterator_type tmp = this->_iterator;
	// 			--tmp;
	// 			return *tmp; }

	// 		pointer	operator->() const { return &(operator*()); }

	// 		reference			operator[](const difference_type &n) const { 
	// 			return *(*this + n); 
	// 		}

	// 		reverse_iterator&	operator++() { 
	// 			--_iterator; 
	// 			return *this; 
	// 		}

	// 		reverse_iterator&	operator++(int) { 
	// 			iterator_type tmp = *this;
	// 			--_iterator;
	// 			return tmp; 
	// 		}

	// 		reverse_iterator&	operator--() {
	// 			++_iterator; 
	// 			return *this;
	// 		}

	// 		reverse_iterator&	operator--(int) { 
	// 			iterator_type tmp = *this;
	// 			++_iterator;
	// 			return tmp;
	// 		}

	// 		reverse_iterator&	operator+=(const difference_type &n) {
	// 			_iterator -= n; 
	// 			return *this; 
	// 		}

	// 		reverse_iterator&	operator-=(const difference_type &n) {
	// 			_iterator += n;
	// 			return *this; 
	// 		}

	// 		reverse_iterator	operator+(const difference_type &n) { return reverse_iterator(_iterator - n); }
	// 		reverse_iterator	operator-(const difference_type &n) { return reverse_iterator(_iterator + n); }
	// 		friend bool			operator==(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator == rhs._iterator); }
	// 		friend bool 		operator!=(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator != rhs._iterator); }
	// 		friend bool 		operator<(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator < rhs._iterator); }
	// 		friend bool 		operator>(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator > rhs._iterator); }
	// 		friend bool 		operator<=(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator <= rhs._iterator); }
	// 		friend bool 		operator>=(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator >= rhs._iterator); }

	// 		friend reverse_iterator	operator+(const difference_type &n, const reverse_iterator & other) { return other + n; }
	// 		friend difference_type	operator-(const reverse_iterator& lhs, reverse_iterator& rhs) { return lhs.base() - rhs.base(); }

	// };	//	class reverse iterator

	
}	//	namespace ft


#endif

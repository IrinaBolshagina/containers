#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <iostream>
#include "vector_iterator.hpp"
#include "vector_reverse_iterator.hpp"
#include "utility.hpp"

namespace ft {

	template < class T, class Allocator = std::allocator<T> >
	class vector {

		public:

		//	Member types
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;

		//	iterators
			typedef RandomAccessIterator<value_type>			iterator;
			typedef RandomAccessIterator<const value_type>		const_iterator;
			typedef reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef reverse_iterator<iterator>					reverse_iterator;
		
		private:
			pointer				_arr;					// указатель на начало массива
			size_type			_size, _capacity;		// размер и емкость
			allocator_type		_alloc;					// аллокатор


		public:

		//	Default constructor. Constructs an empty container with a default allocator
			explicit vector( const allocator_type& alloc = allocator_type() ) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc) {}			 

		//	Fill constructor. Constructs a container with n elements. Each element is a copy of value
			explicit vector( size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): 
			_arr(NULL), _size(n), _capacity(n), _alloc(alloc)  { 
				if (n < 0)
					throw std::out_of_range("vector");
				_arr = _alloc.allocate(n);
				size_type i = 0;
				try {
					for (; i < _size; ++i)
						_alloc.construct(_arr + i, val);
				}
				catch ( std::exception &e ) {
					for (size_type j = 0; j < i; ++j)
						_alloc.destroy(_arr + j);
					_alloc.deallocate(_arr, n);
					throw;
				}
			}


		//	Range constructor. Constructs a container with elements in the range first - last
			template< class InputIt > 
			vector ( InputIt first, InputIt last, const Allocator& alloc = Allocator(), 
			typename enable_if<!is_integral<InputIt>::value>::type* = 0) : _alloc(alloc) {
				_size = last - first;
				_capacity = _size;
				_arr = _alloc.allocate(_capacity);
				size_type i = 0;
				try {
					for (; i < _size; ++i, ++first)
						_alloc.construct(_arr + i, *first);
				}
				catch ( std::exception &e ) {
					for (size_type j = 0; j < i; ++j)
						_alloc.destroy(_arr + j);
					_alloc.deallocate(_arr, _capacity);
					throw;
				}
			} 

		//	Copy constructor
			vector( const vector& other ) : _arr(0), _size(0), _capacity(0), _alloc(other._alloc) { *this = other; }

		//	Destructor. Destructs all object then free memory
			~vector() {
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_arr + i);
				if (_arr)
					_alloc.deallocate(_arr, _capacity);
			}
		
		//	Operator =
			vector& operator= ( const vector& other ) {
				if ( this != &other) {
					this->_alloc = other._alloc;
					for (size_type i = 0; i < _size; ++i)
						_alloc.destroy(_arr + i);
					if (_arr)
						_alloc.deallocate(_arr, _capacity);
					this->_size = other._size;
					this->_capacity = other._capacity;
					_arr = _alloc.allocate(_capacity);
					size_type i = 0;
					try {
						for (; i < _size; ++i)
							_alloc.construct(_arr + i, other._arr[i]);
					}
					catch ( std::exception &e ) {
						for (size_type j = 0; j < i; ++j)
							_alloc.destroy(_arr + j);
						_alloc.deallocate(_arr, _size);
						throw;
					}
				}
				return *this;
			}

		//	Allocator
			allocator_type get_allocator() const { return _alloc; }

		//	Size and capasity
			size_type size() const { return _size; }
			size_type max_size() const { return _alloc.max_size(); }	//	Returns the maximum number of elements that the vector can hold
			size_type capacity() const { return _capacity; }
			bool empty() const { return (_size == 0); }

			void reserve(size_type n) {
			// 1) выделить новую память, если размер больше старой
			// 2) скопировать объекты по новому адресу - проверить если не создались, почистить все
			// 3) удалить старый массив
			// 4) задать новый _capacity
				if (n > _capacity) {
					pointer new_arr = _alloc.allocate(n);
				size_type i = 0;
				try {
					for (; i < _size; ++i)
						_alloc.construct(new_arr + i, _arr[i]);
				}
				catch ( std::exception &e ) {
					for (size_type j = 0; j < i; ++j)
						_alloc.destroy(new_arr + j);
					_alloc.deallocate(new_arr, n);
					throw;
				}
				for(i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				if (_arr) _alloc.deallocate(_arr, _capacity);
				_capacity = n;
				_arr = new_arr;
				}
			};

			void resize (size_type n, value_type val = value_type()) {
				// увеличить емкость если не хватает
				// перекопировать все объекты в новый массив (это сделает reserve)
				// вставить val в пустые ячеки, если новый размер больше старого
				// если новый размер меньше старого, удалить лишние элементы
				
				if (n > _capacity)
					reserve(std::max(n, _capacity * 2));
				for (size_type i = _size; i < n; ++i)
					_alloc.construct(_arr + i, val);
				if (n < _size) {
					reserve (n); 
					for (size_type i = n; i < _size; ++i)
						_alloc.destroy(_arr + i);
				}
				_size = n;
			}

		//	Element access Member Functions

			reference operator[]( size_type pos )	{ return _arr[pos]; }
			const_reference operator[] ( size_type pos ) const	{ return _arr[pos]; }
			reference front()	{ return _arr[0]; }
			const_reference front() const	{ return _arr[0]; }
			reference back()	{ return _arr[_size - 1]; }
			const_reference back() const	{ return _arr[_size - 1]; }
			reference at( size_type pos ) {
				if (pos >= _size)
					throw std::out_of_range("vector index out of range");
				return _arr[pos];
			}
			const_reference at( size_type pos ) const{
				if (pos >= _size)
					throw std::out_of_range("vector index out of range");
				return _arr[pos];
			}

		//	Modifiers Member Functions

			void clear() {
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_arr + i);
				_size = 0;
			}

			//	Replaces the contents with n copies of val value
			void assign( size_type n, const T& val ) {
				this->clear();
				if (n > _capacity) {
					_alloc.deallocate(_arr, _capacity);
					_arr = _alloc.allocate(n);
					_capacity = n;
				}
				size_type i = 0;
				try {
					for (; i < n; ++i)
						_alloc.construct(_arr + i, val);
				}
				catch ( std::exception &e ) {
					for (size_type j = 0; j < i; ++j)
						_alloc.destroy(_arr + j);
					_alloc.deallocate(_arr, _capacity);
					throw;
				}
				_size = n;
			}

			//	Replaces the contents with copies of those in the range (first, last)
			template< class InputIt > 
			void assign( InputIt first, InputIt last,
			typename enable_if<!is_integral<InputIt>::value>::type* = 0 ) {
				size_type n = last - first;
				if (n > _capacity) {
					_alloc.deallocate(_arr, _capacity);
					_arr = _alloc.allocate(n);
					_capacity = n;
				}
				size_type i = 0;
				try {
					for (; i < n; ++i, ++first)
						_alloc.construct(_arr + i, *first);
				}
				catch ( std::exception &e ) {
					for (size_type j = 0; j < i; ++j)
						_alloc.destroy(_arr + j);
					_alloc.deallocate(_arr, _capacity);
					throw;
				}
				_size = n;
			}
			
			void push_back (const value_type& val) {
				if (_capacity == _size) {
					if (_capacity == 0)
						reserve(1);
					else
						reserve(_size * 2);
				}
				_alloc.construct(_arr + _size, val);
				++_size;
			} 

			void pop_back() {
				_alloc.destroy(_arr + _size - 1);
				--_size;
			}

			//	Insert single element to position
			iterator insert (iterator pos, const value_type& val) {
				size_type start = pos.getPointer() - _arr;
				insert (pos, 1, val);
				return (begin() + start);
			}

			//	Insert n elements with val value to pos position, 
			//	effectively increasing the container size by the number of elements inserted
			void insert (iterator pos, size_type n, const value_type& val) {
				if (n == 0)
					return ;
				if (max_size() - _size < n)
					throw std::length_error("vector");
				size_type start = pos.getPointer() - _arr;
				size_type new_cap = _capacity;
				if (_size + n > _capacity)
					new_cap = std::max(_size + n, _capacity * 2);
				pointer new_arr = _alloc.allocate(new_cap);
				size_type i = 0;
				try {
				// copy part before insert
					for (; i < start; ++i)
						_alloc.construct(new_arr + i, _arr[i]);

				// copy insert values
					for (; i < n + start; ++i)
						_alloc.construct(new_arr + i, val);

				// copy part after insert
					for (; i < n + _size; ++i)
						_alloc.construct(new_arr + i, _arr[i - n]);
				}
				catch ( std::exception &e ) {
					for (size_type j = 0; j < i; ++j)
						_alloc.destroy(new_arr + j);
					_alloc.deallocate(new_arr, new_cap);
					throw;
				}
				for (i = 0; i < _size; ++i)
					_alloc.destroy(_arr + i);
				if (_arr)
					_alloc.deallocate(_arr, _capacity);
				_arr = new_arr;
				_size = _size + n;
				_capacity = new_cap;
			}

			//	Insert range from another vector
			template <class InputIt>
			void insert (iterator pos, InputIt first, InputIt last,
			typename enable_if<!is_integral<InputIt>::value>::type* = 0) 
			{
				size_type n = (last - first);
				size_type start = pos.getPointer() - _arr;
				size_type new_cap = _capacity;
				if (_size + n > _capacity)
					new_cap = std::max(_size + n, _capacity * 2);
				pointer new_arr = _alloc.allocate(new_cap);
				size_type i = 0;
				try {
				// copy part before insert
					for (; i < start; ++i)
						_alloc.construct(new_arr + i, _arr[i]);

				// copy insert values
					for (; i < n + start; ++i, ++first)
						_alloc.construct(new_arr + i, *first);

				// copy part after insert
					for (; i < n + _size; ++i)
						_alloc.construct(new_arr + i, _arr[i - n]);
				}
				catch ( std::exception &e ) {
					for (size_type j = 0; j < i; ++j)
						_alloc.destroy(new_arr + j);
					_alloc.deallocate(new_arr, new_cap);
					throw;
				}

				for (i = 0; i < _size; ++i)

					_alloc.destroy(_arr + i);
				if (_arr)
					_alloc.deallocate(_arr, _capacity);
				_arr = new_arr;
				_size = _size + n;
				_capacity = new_cap;
			}
			

			iterator erase (iterator pos) {
				size_type start = pos.getPointer() - _arr;
				for (size_type i = start; i < _size - 1; ++i){
					_alloc.destroy(_arr + i);
					_alloc.construct(_arr + i, _arr[i + 1]);
				}
				_size--;
				_alloc.destroy(_arr + _size - 1);
				return iterator(_arr + start);
			}

			// iterator erase (iterator pos) {	
			// 	pointer new_arr = _alloc.allocate(_capacity);
			// 	size_type start = pos.getPointer() - _arr;			
			// 	size_type i = 0;
			// 	try {
			// 	// copy part before erase
			// 		for (; i < size; ++i)
			// 			_alloc.construct(new_arr + i, _arr[i]);

			// 	// copy part after erase
			// 		for (; i < _size - 1; ++i)
			// 			_alloc.construct(new_arr + i, _arr[i + 1]);
			// 	}
			// 	catch ( std::exception &e ) {
			// 		for (size_type j = 0; j < i; ++j)
			// 			_alloc.destroy(new_arr + j);
			// 		_alloc.deallocate(new_arr, _capacity);
			// 		throw;
			// 	}
			// 	for (i = 0; i < _size; ++i)
			// 		_alloc.destroy(_arr + i);
			// 	// if (_capacity)
			// 		_alloc.deallocate(_arr, _capacity);
			// 	_arr = new_arr;
			// 	_size = _size - 1;
			// 	return (begin() + start);
			// }

				// size_type start = pos.getPointer() - _arr;
				// _alloc.destroy(_arr + start);
				// for (size_type i = start; i < _size; ++i) {
				// 	_alloc.construct(_arr + i, _arr[i + 1]);
				// }
				// _alloc.destroy(_arr + _size - 1);
				// --_size;
				// return (begin() + start); }

				// pointer new_arr = _alloc.allocate(_capacity);
				// size_type start = pos.getPointer() - _arr;		
				// copy_objects(new_arr, _arr, start);
				// copy_objects(new_arr + start, _arr + start + 1, _size - start - 1);
				// for (size_type i = 0; i < _size; ++i)
				// 	_alloc.destroy(_arr + i);
				// if (_capacity)
				// 	_alloc.deallocate(_arr, _capacity);
				// _arr = new_arr;
				// --_size;
				// return (begin() + start);
			// } 

			iterator erase (iterator first, iterator last) {
				size_type start = first.getPointer() - _arr;
				size_type n = end() - last;
				bool last_is_end = (last == end());
				for (; first != last; ++first)
					_alloc.destroy(&(*first));
				size_type i = start;
				while (last < end()){
					if (this->_arr + start)
						_alloc.destroy(_arr + i);
					_alloc.construct(_arr + i, *last);
					++i;
					++last;
				}
				for (size_type i = start + n; i < _size; i++)
					_alloc.destroy(_arr + i);
				_size = start + n;
				return last_is_end ? end() : iterator(_arr + start);
			}
			
			// iterator erase (iterator first, iterator last) {
			// 	pointer new_arr = _alloc.allocate(_capacity);
			// 	size_type start = first.getPointer() - _arr;
			// 	size_type n = (last - first);
				
			// 	copy_objects(new_arr, _arr, start);
			// 	copy_objects(new_arr + start, _arr + start + n, _size - start - n);

			// 	// size_type i = 0;
			// 	// try {
			// 	// // copy part before erase
			// 	// 	for (; i < start; ++i)
			// 	// 		_alloc.construct(new_arr + i, _arr[i]);

			// 	// // copy part after erase
			// 	// 	for (; i < _size - n; ++i)
			// 	// 		_alloc.construct(new_arr + i, _arr[i + n]);
			// 	// }
			// 	// catch ( std::exception &e ) {
			// 	// 	for (size_type j = 0; j < i; ++j)
			// 	// 		_alloc.destroy(new_arr + j);
			// 	// 	_alloc.deallocate(new_arr, _capacity);
			// 	// 	throw;
			// 	// }
			// 	for (size_type i = 0; i < _size; ++i)
			// 		_alloc.destroy(_arr + i);
			// 	_alloc.deallocate(_arr, _capacity);
			// 	_arr = new_arr;
			// 	_size = _size - n;
			// 	return (begin() + start);
			// }

			void swap (vector& other) {
				if (this != &other ) {
					ft::swap(this->_alloc, other._alloc);
					ft::swap(this->_arr, other._arr);
					ft::swap(this->_size, other._size);
					ft::swap(this->_capacity, other._capacity);
				}
			}

			//	Iterators
			iterator begin() { return iterator(_arr); }
			iterator end() { return iterator(_arr + _size); }
			const_iterator begin() const { return const_iterator(_arr); }
			const_iterator end() const { return const_iterator(_arr + _size); }
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	};	// class vector


	// Non-member function overloads

	template <class T, class Allocator>
	void swap (vector<T, Allocator>& x, vector<T, Allocator>& y) {
		x.swap(y);
	}

	// Operators overloads

	template <class T, class Allocator>
	bool operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
		if (x.size() != y.size()) 
			return false;
		for (size_t i = 0; i < x.size(); ++i)
			if (x[i] != y[i])
				return false;
		return true;
	}

	template <class T, class Allocator>
	bool operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
		return !(x == y);
	}

	// template <class T, class Alloc>
	// bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
	// 	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	// }

	template<class _T, class _Alloc>
	bool    operator < (const ft::vector<_T, _Alloc> &lhs, const ft::vector<_T, _Alloc> &rhs)
	{
    	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	// template <class T, class Allocator>
	// bool operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
	// 	size_t n = std::min(x.size(), y.size());
	// 	for (size_t i = 0; i < n; ++i)
	// 		if (x[i] > y[i])
	// 			return false;
	// 	return true;
	// }
	
	template <class T, class Allocator>
	bool operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
		return (y < x);
	}

	template <class T, class Allocator>
	bool operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
		return !(x < y);
	}

	template <class T, class Allocator>
	bool operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
		return !(y < x);
	}

}	// namespace ft

#endif

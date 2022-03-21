#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <iostream>
#include "vector_iterator.hpp"
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
			// reverse_iterator;
			// const_iterator;
			// const_reverse_iterator;
		
		private:
			pointer				_arr;					// указатель на начало массива
			size_type			_size, _capacity;		// размер и емкость
			allocator_type		_alloc;					// аллокатор

		private:
		//	function for protected objects copying
			value_type	*copy_objects( value_type *dst, value_type *src, size_type n ) {
				if (dst == src)
					return dst;
				size_type i = 0;
				try {
					for (; i < n; ++i)
						_alloc.construct(dst + i, src[i]);
				}
				catch ( std::exception &e ) {
					for (size_type j = 0; j < i; ++j)
						_alloc.destroy(dst + j);
					_alloc.deallocate(dst, n);
					throw;
				}
				return dst;
			}

		public:

		//	Constructors:

		// explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _size(n), _capacity(n), _alloc(alloc)
		// {
		// 	_arr = _alloc.allocate(n);
		// 	for(size_type i = 0; i < n; i++)
		// 		_alloc.construct(_arr + i, val);
		// }

		// template <class InputIterator>
        // 	 vector (InputIterator first, InputIterator last,
        //          const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value>::type* = 0) : _alloc(alloc){
		// 	if (first > last)
		// 		throw std::length_error("vector");
		// 	_size = last - first;
		// 	_capacity = _size;
		// 	_arr = _alloc.allocate(_capacity);
		// 	for (difference_type i = 0; i < static_cast<difference_type>(_size); i++)
		// 		_alloc.construct(_arr + i, *(first + i));
		//  }


		//	Default constructor. Constructs an empty container with a default allocator
			explicit vector( const allocator_type& alloc = allocator_type() ) : _arr(NULL), _size(0), _capacity(0), _alloc(alloc) {}

		//	Copy constructor
			vector( const vector& other ) : _arr(0), _size(0), _capacity(0), _alloc(other._alloc) { *this = other; }								 

		//	Fill constructor. Constructs a container with n elements. Each element is a copy of value
			explicit vector( size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): 
			_arr(NULL), _size(n), _capacity(n), _alloc(alloc)  { 
				if (n > 0) {
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

		//	Destructor. Destructs all object then free memory
			~vector() {
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_arr + i);
				if (_capacity)
					_alloc.deallocate(_arr, _capacity);
			}
		
		//	Operator =
			vector& operator= ( const vector& other ) {
				if ( this != &other) {
					this->_alloc = other._alloc;
					for (size_type i = 0; i < _size; ++i)
						_alloc.destroy(_arr + i);
					if (_capacity)
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

				if (_capacity == 0) 
					_arr = _alloc.allocate(n);
				if (n > max_size())
					throw std::length_error("Capacity is greater than vector max_size");
				if (n > _capacity && _capacity > 0) {
					pointer new_arr = _alloc.allocate(n);
					size_type i = 0;
					try {
						for (; i < n; ++i)
							_alloc.construct(new_arr + i, _arr[i]);
					}
					catch ( std::exception &e ) {
						for (size_type j = 0; j < i; ++j)
							_alloc.destroy(new_arr + j);
						_alloc.deallocate(new_arr, n);
						throw;
					}
					for (size_type i = 0; i < n; ++i)
						_alloc.destroy(_arr + i);
					if (_capacity)
						_alloc.deallocate(_arr, _capacity);
					_arr = new_arr;
				}
				_capacity = n;
			}

			void resize (size_type n, value_type val = value_type()) {
				// увеличить емкость если не хватает
				// перекопировать все объекты в новый массив (это сделает reserve)
				// вставить val в пустые ячеки, если новый размер больше старого
				// если новый размер меньше старого, удалить лишние элементы
				
				if (n > _capacity)
					reserve(std::max(n, _capacity * 2));
				for (size_type i = _size; i < n; ++i)
					_alloc.construct(_arr + i, val); // exception?
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

			void assign( size_type n, const T& val ) {
				this->clear();
				if (n > _capacity) {
					_alloc.deallocate(_arr, _capacity);
					_arr = _alloc.allocate(n);
					_capacity = n;
				}
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(_arr + i, val); // exception?
				_size = n;
			}

			// template< class InputIt > void assign( InputIt first, InputIt last ) {}  // !!!
			
			void push_back (const value_type& val) {
				if (_capacity == _size && _capacity > 0)
					reserve(_capacity * 2);
				if (_capacity == 0)
					reserve(1);
				_alloc.construct(_arr + _size, val);
				++_size;
			} 

			void pop_back() {
				_alloc.destroy(_arr + _size - 1);
				--_size;
			}

				// Insert single element to position
			iterator insert (iterator pos, const value_type& val) {
				size_type start = pos.getPointer() - _arr;
				insert (pos, 1, val);
				return (begin() + start);
			}

			//	Insert n elements with value to position, 
			//	effectively increasing the container size by the number of elements inserted
			void insert (iterator pos, size_type n, const value_type& val) {
				size_type start = pos.getPointer() - _arr;
				size_type end = _size - start;
				pointer new_arr = _alloc.allocate(std::max(_size + n, _capacity * 2));
				copy_objects(new_arr, _arr, start);
				for (size_type i = 0; i < n; ++i)
					_alloc.construct(new_arr + start + i, val);
				copy_objects(new_arr + start + n, _arr + start, end);
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_arr + i);
				if (_capacity)
					_alloc.deallocate(_arr, _capacity);
				_arr = new_arr;
				_size = _size + n;
			}

			//	Insert range from another vector
			template <class InputIt>
			void insert (iterator pos, InputIt first, InputIt last,
			typename enable_if<!is_integral<InputIt>::value>::type* = 0) 
			{
			// void insert (iterator pos, iterator first, iterator last) {
				size_type n = (last - first);
				size_type start = pos.getPointer() - _arr;
				size_type end = _size - start;
				pointer new_arr = _alloc.allocate(std::max(_size + n, _capacity * 2));
				copy_objects(new_arr, _arr, start);
				for (size_type i = 0; i < n; ++i, ++first)
					_alloc.construct(new_arr + start + i, *first);
				copy_objects(new_arr + start + n, _arr + start, end);
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_arr + i);
				if (_capacity)
					_alloc.deallocate(_arr, _capacity);
				_arr = new_arr;
				_size = _size + n;
			}
			
			iterator erase (iterator pos) {
				// size_type start = pos.getPointer() - _arr;
				// _alloc.destroy(_arr + start);
				// for (size_type i = start; i < _size; ++i)
				// 	_alloc.construct(_arr + i, _arr[i + 1]);
				// --_size;
				// return (begin() + start);
				pointer new_arr = _alloc.allocate(_capacity);
				size_type start = pos.getPointer() - _arr;		
				copy_objects(new_arr, _arr, start);
				copy_objects(new_arr + start, _arr + start + 1, _size - start - 1);
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_arr + i);
				if (_capacity)
					_alloc.deallocate(_arr, _capacity);
				_arr = new_arr;
				--_size;
				return (begin() + start);
			} 
			
			iterator erase (iterator first, iterator last) {
				pointer new_arr = _alloc.allocate(_capacity);
				size_type start = first.getPointer() - _arr;
				size_type n = (last - first);
				copy_objects(new_arr, _arr, start);
				copy_objects(new_arr + start, _arr + start + n, _size - start - n);
				for (size_type i = 0; i < _size; ++i)
					_alloc.destroy(_arr + i);
				if (_capacity)
					_alloc.deallocate(_arr, _capacity);
				_arr = new_arr;
				_size = _size - n;
				return (begin() + start);
			}

			void swap (vector& other) {
				if (this != &other ) {
					std::swap(this->_alloc, other._alloc);
					std::swap(this->_arr, other._arr);
					std::swap(this->_size, other._size);
					std::swap(this->_capacity, other._capacity);
				}
			}

			//	Iterators
			iterator begin() { return iterator(_arr); }
			//const_iterator begin() const { return const_iterator(_arr); }
			iterator end() { return iterator(_arr + _size); }
			// const_iterator  end() const { return const_iterator(_arr + _size); }
			// reverse_iterator rbegin() { return reverse_iterator(_arr); }
			// reverse_iterator rend() { return reverse_iterator(_arr + _size); }
			// const_reverse_iterator rbegin() const { return const_reverse_iterator(_arr); }
			// const_reverse_iterator rend() const { return const_reverse_iterator(_arr + _size); }

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

	template <class T, class Allocator>
	bool operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y) {
		size_t n = std::min(x.size(), y.size());
		for (size_t i = 0; i < n; ++i)
			if (x[i] > y[i])
				return false;
		return true;
	}
	
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

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "utility.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator : public Iterator {

	public:
	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

	private:
		iterator_type	_iterator;

	public:
	//	constructors and staff
		reverse_iterator() : _iterator() {}

		explicit reverse_iterator (iterator_type it) : _iterator(it) {}

		template <class Iter> 
		reverse_iterator (const reverse_iterator<Iter> &other) { 
			this->_iterator = other._iterator; 
		}

		virtual ~reverse_iterator() {}

		reverse_iterator &operator=( const reverse_iterator &other) {
			if(this != &other)
				this->_iterator = other._iterator;
			return *this;
		}

	//	member functions
		iterator_type	base() const { return _iterator; }

	//	operators overload
		reference	operator*() const { 
			iterator_type tmp = this->_iterator;
			--tmp;
			return *tmp; }

		pointer	operator->() const { return &(operator*()); }

		reference	operator[](const difference_type &n) const { 
			return *(*this + n); 
		}
		
		reverse_iterator&	operator++() { 
			--_iterator; 
			return *this; 
		}

		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			--_iterator;
			return tmp;
		}

		reverse_iterator& operator--() {
			++_iterator;
			return*this;
		}

		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			++_iterator;
			return tmp;
		}

		reverse_iterator& operator+=(difference_type n) {
			_iterator -= n;
			return *this;
		}


		reverse_iterator& operator-=(difference_type n) {
			_iterator += n;
			return *this;
		}

		reverse_iterator	operator+(const difference_type &n) { return reverse_iterator(_iterator - n); }
		reverse_iterator	operator-(const difference_type &n) { return reverse_iterator(_iterator + n); }
		// friend bool			operator==(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator == rhs._iterator); }
		// friend bool 		operator!=(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator != rhs._iterator); }
		// friend bool 		operator<(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator < rhs._iterator); }
		// friend bool 		operator>(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator > rhs._iterator); }
		// friend bool 		operator<=(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator <= rhs._iterator); }
		// friend bool 		operator>=(const reverse_iterator& lhs, const reverse_iterator& rhs) { return (lhs._iterator >= rhs._iterator); }
		
		// friend reverse_iterator	operator+(const difference_type &n, const reverse_iterator & other) { return other + n; }
		// friend difference_type	operator-(const reverse_iterator& lhs, reverse_iterator& rhs) { return lhs.base() - rhs.base(); }

	};

	template <class Iterator>
	bool operator==( const reverse_iterator<Iterator>& lhs, 
		const reverse_iterator<Iterator>& rhs) {
		return(lhs.base() == rhs.base()); 
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		return(lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		return (lhs._iterator < rhs._iterator);
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs);

	template <class Iterator>
	bool operator>(
			const reverse_iterator<Iterator>& lhs,
			 const reverse_iterator<Iterator>& rhs);

	template <class Iterator>
	bool operator>=(
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs);

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
	{
		return(rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
	{
		return(lhs.base() - rhs.base());
	}

}; //	namespace ft

#endif

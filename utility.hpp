#ifndef UTILITY_HPP
# define UTILITY_HPP

#include <iterator>
#include <iostream>

namespace ft {

	template< class Iter >
	class iterator_traits {
		public:
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template< class T >
	class iterator_traits<T*> {
		public:
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T*									pointer;
		typedef T&									reference;
	};

	template< class T >
	class iterator_traits<const T*> {
		public:
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag		iterator_category;
		typedef const T*							pointer;
		typedef const T&							reference;
	};

	// enable if

	template<bool condition, class T = void>
	struct enable_if;

	template <typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	// is integral

	template<class T, bool v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};

	template <class T> struct is_integral				: public ft::integral_constant<T, false> {};
	template <> struct is_integral<bool>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<char>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<char16_t>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<short>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<int>					: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<long>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long long>	: public ft::integral_constant<bool, true> {};
	
	// pair

	template <class T1, class T2>
    struct pair
	{
		typedef T1		first_type;
		typedef T2		second_type;

		first_type		first;
		second_type		second;

 		pair() : first(first_type()), second(second_type()) {}

		pair(const first_type &x, const second_type &y) : first(x), second(y) {}

		pair(const pair &other) : first(other.first), second(other.second) {}

        template <class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

        pair&	operator = (const pair &other) {
 			if (this != &other) {
 				first = other.first;
				second = other.second;
			}
 			return *this;
		}
		
	};

	//	pair comparison operators
	template <class T1, class T2>
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(rhs < lhs); }

	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (rhs < lhs); }

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(lhs < rhs); }


	//	make pair
	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

	//	lexicographical compare
	template<class _InputIt1, class _InputIt2>
    bool    lexicographical_compare(_InputIt1 first1, _InputIt1 last1, _InputIt2 first2, _InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template<class _InputIt1, class _InputIt2, class _Compare>
    bool    lexicographical_compare(_InputIt1 first1, _InputIt1 last1, _InputIt2 first2, _InputIt2 last2, _Compare comp)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            if (comp(*first1, *first2)) return true;
            if (comp(*first2, *first1)) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
	    return true;
	}

	// ft::swap
	template <class T>
	void swap(T &x, T &y) {
		T tmp(x);
		x = y;
		y = tmp;
	}

}	//	namespace ft


#endif

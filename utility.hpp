#ifndef UTILITY_HPP
# define UTILITY_HPP

#include <iterator>
#include <iostream>
// #include "map.hpp"
// #include "vector.hpp"

namespace ft {

	//	iterator traits

	// template <class Iterator> class iterator_traits
	// {
	// 	public:
	// 		typedef typename Iterator::difference_type	difference_type;
	// 		typedef typename Iterator::value_type				value_type;
	// 		typedef typename Iterator::pointer			pointer;
	// 		typedef typename Iterator::reference			reference;
	// 		typedef typename Iterator::iterator_category	iterator_category;
	// };

	// template <class T> class iterator_traits<T*>
	// {
	// 	public:
	// 		typedef std::ptrdiff_t	difference_type;
	// 		typedef T				value_type;
	// 		typedef T*			pointer;
	// 		typedef T&			reference;
	// 		typedef	std::random_access_iterator_tag	iterator_category;
	// };

	// template <class T> class iterator_traits<const T*>
	// {
	// 	public:
	// 		typedef std::ptrdiff_t	difference_type;
	// 		typedef const T				value_type;
	// 		typedef const T*			pointer;
	// 		typedef const T&			reference;
	// 		typedef	std::random_access_iterator_tag	iterator_category;
	// };




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
	
	// template<typename T>	struct is_integral { static const bool value = false; };
	// template<>				struct is_integral<bool> { static const bool value = true; };
	// template<>				struct is_integral<char> { static const bool value = true; };
	// template<>				struct is_integral<signed char> { static const bool value = true; };
	// template<>				struct is_integral<unsigned char> { static const bool value = true; };
	// template<>				struct is_integral<wchar_t> { static const bool value = true; };
	// template<>				struct is_integral<char16_t> { static const bool value = true; };
	// template<>				struct is_integral<short> { static const bool value = true; };
	// template<>				struct is_integral<unsigned short> { static const bool value = true; };
	// template<>				struct is_integral<int> { static const bool value = true; };
	// template<>				struct is_integral<unsigned int> { static const bool value = true; };
	// template<>				struct is_integral<long> { static const bool value = true; };
	// template<>				struct is_integral<unsigned long> { static const bool value = true; };
	// template<>				struct is_integral<long long> { static const bool value = true; };
	// template<>				struct is_integral<unsigned long long> { static const bool value = true; };

	// pair

	template <class T1, class T2>
    struct pair
	{
		typedef T1		first_type;
		typedef T2		second_type;

		first_type		first;
		second_type		second;

        //	default constructor
 		pair() : first(first_type()), second(second_type()) {}

        //	initialization constructor
		pair(const first_type &x, const second_type &y) : first(x), second(y) {}

		//	copy constructor
		pair(const pair &other) : first(other.first), second(other.second) {}

        //	converting constructor
        template <class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

    	//	assignment operator
        pair&    operator = (const pair &other) {
 			if (this != &other) {
 				first = other.first;
				second = other.second;
			}
 			return *this;
		}
	};

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

	template <class T>
	void swap(T &x, T &y) {
		T tmp(x);
		x = y;
		y = tmp;
	}

}	//	namespace ft

// namespace std {
// 	template <class T, class A>
// 	void swap(ft::vector<T, A> &v1, ft::vector<T, A> &v2 ) {
// 		v1.swap(v2);
// 	}

// 	// template <class Key, class T, class Compare, class A>
// 	// void swap(ft::map<Key, T, Compare, A> &m1, ft::map<Key, T, Compare, A> &m2 ) {
// 	// 	m1.swap(m2);
// 	// }
// }

#endif

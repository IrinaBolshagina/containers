#ifndef UTILITY_HPP
# define UTILITY_HPP

#include <iterator>

namespace ft {

	template< class Iter >
	struct iterator_traits {
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template< class T >
	struct iterator_traits<T*> {
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T*									pointer;
		typedef T&									reference;
	};

	template< class T >
	struct iterator_traits<const T*> {
		typedef T									value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag		iterator_category;
		typedef const T*							pointer;
		typedef const T&							reference;
	};

	template<bool condition, class T = void>
	struct enable_if;

	template <typename T>
	struct enable_if<true, T> {
		typedef T type;
	};
	
	template<typename T>	struct is_integral { static const bool value = false; };
	template<>				struct is_integral<bool> { static const bool value = true; };
	template<>				struct is_integral<char> { static const bool value = true; };
	template<>				struct is_integral<signed char> { static const bool value = true; };
	template<>				struct is_integral<unsigned char> { static const bool value = true; };
	template<>				struct is_integral<wchar_t> { static const bool value = true; };
	template<>				struct is_integral<char16_t> { static const bool value = true; };
	template<>				struct is_integral<short> { static const bool value = true; };
	template<>				struct is_integral<unsigned short> { static const bool value = true; };
	template<>				struct is_integral<int> { static const bool value = true; };
	template<>				struct is_integral<unsigned int> { static const bool value = true; };
	template<>				struct is_integral<long> { static const bool value = true; };
	template<>				struct is_integral<unsigned long> { static const bool value = true; };
	template<>				struct is_integral<long long> { static const bool value = true; };
	template<>				struct is_integral<unsigned long long> { static const bool value = true; };


}	//	namespace ft

#endif

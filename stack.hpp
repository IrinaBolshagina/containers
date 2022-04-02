#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <vector>

namespace ft {

	template <class T, class Container = std::vector<T> > 
	class stack {

		public:

		// Member types
			typedef T								value_type;
			typedef Container						container_type;
			typedef typename Container::size_type	size_type;

		protected:

		// Underlying container (vector by default)
			container_type							c;

		public:

		// Constructors and stuff
			explicit stack(const container_type& cont = container_type()) : c(cont) {}
			stack( const stack& other ) : c(other.c) {}
			~stack() {}
			stack& operator=( const stack& other ) {
				c = other.c;
				return *this;
			}


		// Member functions
			bool empty() const						{ return c.empty(); }
			size_type size() const					{ return c.size(); }
			value_type& top() 						{ return c.back(); }
			value_type& top() const 				{ return c.back(); }
			void push( const value_type& v )		{ c.push_back(v); }
			void pop()								{ c.pop_back(); }


		// Operators overload
			friend bool operator==( const stack& one, const stack& two)	{ return ( one._container == two._container ); }
			friend bool operator!=( const stack& one, const stack& two)	{ return ( one._container != two._container ); }
			friend bool operator<( const stack& one, const stack& two)	{ return ( one._container < two._container ); }
			friend bool operator<=( const stack& one, const stack& two)	{ return ( one._container <= two._container ); }
			friend bool operator>( const stack& one, const stack& two)	{ return ( one._container > two._container ); }
			friend bool operator>=( const stack& one, const stack& two)	{ return ( one._container >= two._container ); }
	
	};	// class stack

}	// namespace ft

#endif

# Сontainers

In this study project, I implemented a few container types of the C++98 standard template
library. 

## Vector
A vector is a dynamic array whose memory is allocated in a chunk using std::allocator, it has an iterator and a reverse_iterator.
The vector implementation stores:
 *   _array (pointer to the beginning of the array)
 *   _size (size)
 *   _capacity
 *   _alloc (allocator)
    

## Map
Is a sorted associative container that contains key-value pairs with unique keys. It's implemented in a Binary Tree. The key-value pair is a node of the tree. It has an iterator and a reverse_iterator. 


## Stack
It uses vector class as default underlying container. But it also compatible with other containers. Has no iterator.




Also was implemented:
* std::iterator_traits
* std::reverse_iterator
* std::enable_if
* std::is_integral
* std::lexicographical_compare
* std::pair
* std::make_pair

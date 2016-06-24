#include <iostream>

template<typename Item>
class ListIter : public std::iterator_traits<std::forward_iterator_tag, Item>
{
	Item *ptr;

	ListIter(Item *p = 0) : ptr(p) {}

	Item& operator*() const { return *ptr; }

	Item* operatoe->() const { return ptr; }

	ListIter& operator++()
	{
		ptr = ptr->next();
		return *this;
	}

	ListIter operator++(int)
	{
		ListIter tmp = *this;
		++*this;
		return tmp;
	}

	bool operator==(const ListIter &rhs) const { return ptr == rhs.ptr; }

	bool operator!=(const ListIter &rhs) const { return ptr != rhs.ptr; }
};
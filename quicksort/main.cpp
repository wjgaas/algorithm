#include <iostream>

template<class ForwardIt, class UnarrayPredicate>
ForwardIt find_if_not(ForwardIt first, ForwardIt last, UnarrayPredicate p)
{
	for (; first != last; ++first)
	{
		if (!p(*first))
			return first;
	}

	return last;
}

template<class ForwardIt, class UnarrayPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnarrayPredicate p)
{
	first = find_if_not(first, last, p);
	if (first == last) return first;

	for (ForwardIt it = std::next(first); it != last; ++it)
	{
		if (p(*it))
		{
			std::iter_swap(it, first);
			++first;
		}
	}

	return first;
}

template<class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last)
{
	if (first == last) return;

	auto pivot = *std::next(first, std::distance(first, last) / 2);

	ForwardIt middle1 = partition(first, last, \
		[pivot](ForwardIt::value_type &em){return em < pivot; });

	ForwardIt middle2 = partition(middle1, last, \
		[pivot](ForwardIt::value_type &em){return  !(pivot< em); });

	quicksort(first, middle1);
	quicksort(middle2, last);
}

int main()
{
	//int a[] = {9,8,4,5,7,3,1,2};

	std::string a = "98457312";

	quicksort(std::begin(a), std::end(a));
}
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>
#include <iterator>

template < typename RandomAccessIterator > void order(RandomAccessIterator first, RandomAccessIterator last)
{
	using T = typename std::iterator_traits<RandomAccessIterator>::value_type;

	for (auto i = std::next(first); i != last; ++i)
	{
		for (auto j = i; j != first; --j)
		{
			if (*std::prev(j) > *j)
				std::swap(*j, *std::prev(j));
			else
				break;
		}
	}
}

template < typename RandomAccessIterator, typename ValueType >
RandomAccessIterator partition(RandomAccessIterator first, RandomAccessIterator last, ValueType pivot)
{
	RandomAccessIterator smaller = first;

	for (RandomAccessIterator cur = first; cur != last; ++cur)
	{
		if (*cur < pivot)
		{
			std::swap(*cur, *smaller);
			++smaller;
		}
	}
	return smaller;
}

template < typename T > T choose_pivot(T p1, T p2, T p3) {
	if ((p1 <= p2 && p2 <= p3) || (p1 >= p2 && p2 >= p3)) return p2;
	else if ((p2 <= p1 && p1 <= p3) || (p2 >= p1 && p1 >= p3)) return p1;
	else return p3;
}

template < typename RandomAccessIterator >
void sort(RandomAccessIterator first, RandomAccessIterator last)
{
	if (std::distance(first, last) > 64)
	{
		auto middle_it = first + std::distance(first, last) / 2;
		using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
		ValueType pivot = choose_pivot(*first, *middle_it, *std::prev(last));

		auto middle = partition(first, last, pivot);

		sort(first, middle);
		sort(middle, last);
	}
	else
	{
		order(first, last);
	}
}



int main()
{
	std::size_t size = 1'000;
	std::vector < int > vector(size, 0);
	std::vector < long > vector1(size, 0);

	for (std::size_t i = 0; i < size; ++i)
	{
		vector[i] = size - i;
		vector1[i] = size - i * i - 3 * i + 10;
	}

	sort(std::begin(vector), std::end(vector));
	sort(std::begin(vector1), std::end(vector1));

	assert(std::ranges::is_sorted(vector));
	assert(std::ranges::is_sorted(vector1));
}

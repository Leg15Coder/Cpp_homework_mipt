#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>


template < typename T > void order(std::vector < T > & vector, std::size_t left, std::size_t right)
{
	if (left >= right) return;
	for (auto i = left + 1; i < right; ++i)
	{
		for (auto j = i; j > left; --j)
		{
			if (vector[j - 1] > vector[j]) 
				std::swap(vector[j], vector[j - 1]);
		}
	}
}

template < typename T > std::size_t partition(std::vector < T > & vector_1, std::size_t left, std::size_t right, T pivot)
{
	std::size_t smaller = left;

	for (std::size_t cur = left; cur < right; ++cur) 
	{
		if (vector_1.at(cur) < pivot) 
		{
			std::swap(vector_1[cur], vector_1[smaller]);
			smaller++;
		}
	}

	return smaller;
}

template < typename T > T choose_pivot(T p1, T p2, T p3) {
	if ((p1 <= p2 && p2 <= p3) || (p1 >= p2 && p2 >= p3)) return p2;
	else if ((p2 <= p1 && p1 <= p3) || (p2 >= p1 && p1 >= p3)) return p1;
	else return p3;
}

template < typename T > void sort(std::vector < T > & vector, std::size_t left, std::size_t right, std::size_t threshold)
{
    while (right - left > threshold)
    {
        if (right - left <= 1) {
            break;
        }

        auto middle_index = left + (right - left) / 2;
        T pivot = choose_pivot(vector.at(left), vector.at(middle_index), vector.at(right - 1));

        auto middle = partition(vector, left, right, pivot);

        if (middle == left) {
            middle++;
        }
        
        if (middle - left < right - middle) {
            sort(vector, left, middle, threshold);
            left = middle;
        } else {
            sort(vector, middle, right, threshold);
            right = middle;
        }
    }
    order(vector, left, right);
}


template < typename T > void sort(std::vector < T > & vector, std::size_t threshold)
{
	if (!vector.empty())
		sort(vector, 0, std::size(vector), threshold);
}

template < typename T > void sort(std::vector < T > & vector)
{
	if (!vector.empty())
		sort(vector, 0, std::size(vector), 64);
}
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>


void order(std::vector < int > & vector, std::size_t left, std::size_t right)
{
	for (auto i = left + 1; i < right; ++i)
	{
		for (auto j = i; j > left; --j)
		{
			if (vector[j - 1] > vector[j]) 
				std::swap(vector[j], vector[j - 1]);
		}
	}
}

std::size_t partition(std::vector < int > & vector_1, std::size_t left, std::size_t right, int pivot)
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

void sort(std::vector < int > & vector, std::size_t left, std::size_t right)
{
	if (right - left > 64)
	{
		auto pivot_index = left + (right - left) / 2;
		auto pivot = vector.at(pivot_index);

		auto middle = partition(vector, left,   right, pivot);

		sort(vector, left, middle);

		sort(vector, middle, right);
	}
	else
	{
		order(vector, left,   right );
	}
}

void sort(std::vector < int > & vector)
{
	sort(vector, 0, std::size(vector));
}

int main()
{
	std::size_t size = 1'000;
	std::vector < int > vector(size, 0);

	for (std::size_t i = 0; i < size; ++i)
	{
		vector[i] = size - i;
	}

	sort(vector);

	assert(std::ranges::is_sorted(vector));
}

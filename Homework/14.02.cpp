#include <algorithm>
#include <cassert>
#include <functional>
#include <future>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>
#include <iostream>
#include <typeinfo>

/////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V, typename F > 
void parallel_for_each(V view, F func)
{
	auto begin = std::begin(view), end = std::end(view);

	if (auto size = std::distance(begin, end); size > 64)
	{
        std::ranges::subrange range(begin, std::next(begin, size / 2));

		auto future = std::async([range, func]() {
            parallel_for_each(range, func);
        });

		parallel_for_each(std::ranges::subrange(std::end(range), end), func);

		future.wait();
	}
	else
	{
		std::ranges::for_each(view, func);
	}
}

/////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(1 << 10, 0);
	std::ranges::iota(vector, 1);

    auto increment = [](int& x) { ++x; };

	parallel_for_each(std::views::all(vector), increment);

    bool success = true;
    for (int x : vector) {
        if (x < 2) {
            success = false;
            break;
        }
    }
    
    if (success) {
        std::cout << "Validation successful.\n";
    } else {
        std::cerr << "Validation failed!\n";
        return 1;
    }

    auto std_ret = std::for_each(vector.begin(), vector.end(), increment);

    std::cout << "std::for_each return type:      " << typeid(std_ret).name() << " (Function Object)\n";
}

/////////////////////////////////////////////////////////////////////////////

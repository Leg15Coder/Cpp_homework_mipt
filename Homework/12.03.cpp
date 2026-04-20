#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <cstddef>
#include <benchmark/benchmark.h>

std::string_view longest_palindrome(std::string_view s)
{
    if (s.length() < 2)
    {
        return s;
    }

    const size_t n = s.length();
    std::vector<bool> cache(n * n, false);

    size_t max_len = 1;
    size_t start_index = 0;

    for (size_t i = 0; i < n; ++i)
    {
        cache[i * n + i] = true;
    }

    for (size_t i = 0; i < n - 1; ++i)
    {
        if (s[i] == s[i + 1])
        {
            cache[i * n + (i + 1)] = true;
            if (2 > max_len) {
                max_len = 2;
                start_index = i;
            }
        }
    }

    for (size_t len = 3; len <= n; ++len)
    {
        for (size_t i = 0; i <= n - len; ++i)
        {
            size_t j = i + len - 1;
            if (cache[(i + 1) * n + (j - 1)] && s[i] == s[j])
            {
                cache[i * n + j] = true;
                if (len > max_len)
                {
                    max_len = len;
                    start_index = i;
                }
            }
        }
    }

    return s.substr(start_index, max_len);
}

static void BM_LongestPalindrome(benchmark::State& state) {
  std::string s(state.range(0), 'a');
  s += std::string(state.range(0), 'b');
  s += "racecar";
  s += std::string(state.range(0), 'c');

  for (auto _ : state) {
    benchmark::DoNotOptimize(longest_palindrome(s));
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_LongestPalindrome)->Range(8, 512)->Complexity(benchmark::oNSquared);

int main(int argc, char** argv)
{
    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    benchmark::RunSpecifiedBenchmarks();
}

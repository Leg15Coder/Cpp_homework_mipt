#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <benchmark/benchmark.h>

size_t ExtractEmails(const std::string& text) {
    static const std::regex email_regex(R"([\w.%+-]+@([\w.-]+\.[a-zA-Z]{2,}))");
    auto emails_begin = std::sregex_iterator(text.begin(), text.end(), email_regex);
    auto emails_end = std::sregex_iterator();
    
    size_t count = 0;
    for (auto it = emails_begin; it != emails_end; ++it) {
        benchmark::DoNotOptimize((*it)[0].str());
        benchmark::DoNotOptimize((*it)[1].str());
        count++;
    }
    return count;
}

static void BM_EmailExtraction(benchmark::State& state) {
  std::string text_chunk = "Some non-email text here to make things a bit more realistic. Then an email: test.email@example.com. ";
  std::string text;
  for (int i = 0; i < state.range(0); ++i) {
    text += text_chunk;
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(ExtractEmails(text));
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_EmailExtraction)->Range(1, 256)->Complexity(benchmark::oN);

int main(int argc, char** argv)
{
    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    benchmark::RunSpecifiedBenchmarks();
}

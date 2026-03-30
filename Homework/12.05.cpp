#include <cctype>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <cmath>
#include <stdexcept>
#include <benchmark/benchmark.h>

class Stream
{
public:
    using token_t = std::variant<char, double, std::string>;
    Stream(std::string const& string) : m_stream(string + ';') {}
    auto empty()
    {
        return m_stream.peek() == ';';
    }
    auto get()
    {
        if (m_has_token)
        {
            m_has_token = false;
            return m_token;
        }
        char x = '\0';
        m_stream >> x;
        switch (x)
        {
            case '+': case '-': case '*': case '/': case '(': case ')':
            case '[': case ']': case '{': case '}': case '%': case '^': case '!':
            case ';':
                return token_t(x);
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case '.':
            {
                m_stream.unget();
                double y = 0.0;
                m_stream >> y;
                return token_t(y);
            }
            default:
            {
                if (std::isalpha(x)) {
                    std::string string(1, x);
                    while (m_stream.get(x) && (std::isalpha(x) || std::isdigit(x)))
                    {
                        string += x;
                    }
                    if (!std::isspace(x))
                    {
                        m_stream.unget();
                    }
                    return token_t(string);
                }
                throw std::runtime_error("Bad token");
            }
        }
    }
    void put(token_t const& token)
    {
        m_token = token;
        m_has_token = true;
    }
private:
    std::stringstream m_stream;
    token_t m_token;
    bool m_has_token = false;
};

class Calculator
{
public:
    double parse(const std::string& line) {
        Stream stream(line);
        if (stream.empty()) return 0.0;
        return expression(stream);
    }
private:
    double expression(Stream& stream);
    double term(Stream& stream);
    double power(Stream& stream);
    double factorial(Stream& stream);
    double primary(Stream& stream);
    double do_factorial(double n);
    std::unordered_map<std::string, double> m_variables;
};

double Calculator::do_factorial(double n) {
    if (n < 0) throw std::runtime_error("Factorial of negative number");
    if (n == 0) return 1;
    double result = 1;
    for (int i = 1; i <= static_cast<int>(n); ++i) {
        result *= i;
    }
    return result;
}

double Calculator::primary(Stream& stream)
{
    auto token = stream.get();
    if (std::holds_alternative<double>(token))
    {
        return std::get<double>(token);
    }
    if (std::holds_alternative<char>(token))
    {
        char c = std::get<char>(token);
        switch (c)
        {
            case '(': { double x = expression(stream); token = stream.get(); if (std::get<char>(token) != ')') throw std::runtime_error("')' expected"); return x; }
            case '[': { double x = expression(stream); token = stream.get(); if (std::get<char>(token) != ']') throw std::runtime_error("']' expected"); return x; }
            case '{': { double x = expression(stream); token = stream.get(); if (std::get<char>(token) != '}') throw std::runtime_error("'}' expected"); return x; }
            case '+': return primary(stream);
            case '-': return -primary(stream);
            default: stream.put(token); throw std::runtime_error("primary expected");
        }
    }
    throw std::runtime_error("primary expected");
}

double Calculator::factorial(Stream& stream)
{
    double x = primary(stream);
    auto token = stream.get();
    if (std::holds_alternative<char>(token) && std::get<char>(token) == '!') {
        return do_factorial(x);
    }
    stream.put(token);
    return x;
}

double Calculator::power(Stream& stream)
{
    double left = factorial(stream);
    auto token = stream.get();
    if (std::holds_alternative<char>(token) && std::get<char>(token) == '^') {
        double right = power(stream);
        return std::pow(left, right);
    }
    stream.put(token);
    return left;
}

double Calculator::term(Stream& stream)
{
    double x = power(stream);
    auto token = stream.get();
    while (true)
    {
        if (std::holds_alternative<char>(token)) {
            char c = std::get<char>(token);
            switch (c)
            {
                case '*': x *= power(stream); token = stream.get(); break;
                case '/': { double d = power(stream); if (d == 0) throw std::runtime_error("divide by zero"); x /= d; token = stream.get(); break; }
                case '%': { double d = power(stream); if (d == 0) throw std::runtime_error("divide by zero for modulo"); x = std::fmod(x, d); token = stream.get(); break; }
                default: stream.put(token); return x;
            }
        } else { stream.put(token); return x; }
    }
}

double Calculator::expression(Stream& stream)
{
    double x = term(stream);
    auto token = stream.get();
    while (true)
    {
        if (std::holds_alternative<char>(token)) {
             char c = std::get<char>(token);
            switch (c)
            {
                case '+': x += term(stream); token = stream.get(); break;
                case '-': x -= term(stream); token = stream.get(); break;
                default: stream.put(token); return x;
            }
        } else { stream.put(token); return x; }
    }
}

static void BM_CalculatorParse(benchmark::State& state) {
  std::string expr = "{[2+3!]*100/(2^5)} % 7";
  Calculator calc;
  for (auto _ : state) {
    benchmark::DoNotOptimize(calc.parse(expr));
  }
}
BENCHMARK(BM_CalculatorParse);

int main(int argc, char** argv)
{
    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    benchmark::RunSpecifiedBenchmarks();
}

#include <type_traits>
#include <limits>
#include <concepts>
#include <iostream>
#include <cassert>

template<typename T>
concept DoubleType = std::is_same_v<T, double>;


constexpr double comp([[maybe_unused]] bool is_max, double current) {
    return current;
}


template<typename T, typename... Args>
constexpr double comp(bool is_max, double current, T first, Args... args);


template<DoubleType T, typename... Args>
constexpr double comp(bool is_max, double current, T first, Args... args) {
    double tmp = ((first < current) ^ is_max) ? first : current;
    return comp(is_max, tmp, args...);
}


template<typename T, typename... Args>
constexpr double comp(bool is_max, double current, [[maybe_unused]] T first, Args... args) {
    return comp(is_max, current, args...);
}


template<typename... Args>
constexpr double max(Args... args) {
    double initial = std::numeric_limits<double>::min();
    return comp(true, initial, args...);
}


template<typename... Args>
constexpr double min(Args... args) {
    double initial = std::numeric_limits<double>::max();
    return comp(false, initial, args...);
}


template<typename T>
constexpr double return_if_corrert_type(T val) {
    if constexpr (DoubleType<T>) return double(val);
    else return 0.0;
}


template<typename... Args>
constexpr double sum(Args... args) {
    return (... + return_if_corrert_type(args));
}


template<typename... Args>
constexpr double average(Args... args) {
    double total = sum(args...);
    std::size_t count = ((DoubleType<Args> ? 1 : 0) + ...);
    return count > 0 ? total / count : 0.0;
}


int main() {
    double result = 0.0;
    
    result = max(1.5, 2, 3.7, 4.0f, 5.2, "string", 'a');
    std::cout << "Max: " << result << std::endl;
    assert(std::abs(result - 5.2) < std::numeric_limits<double>::epsilon());
        
    result = min(1.5, 2, 3.7, 4.0f, 5.2, "string", 'a');
    std::cout << "Min: " << result << std::endl;
    assert(std::abs(result - 1.5) < std::numeric_limits<double>::epsilon());
    
    result = sum(1.5, 2, 3.7, 4.0f, 5.2, "string", 'a');
    std::cout << "Sum: " << result << std::endl;
    assert(std::abs(result - (1.5 + 3.7 + 5.2)) < std::numeric_limits<double>::epsilon());
    
    result = average(1.5, 2, 3.7, 4.0f, 5.2, "string", 'a');
    std::cout << "Average: " << result << std::endl;
    double expected_avg = (1.5 + 3.7 + 5.2) / 3;
    assert(std::abs(result - expected_avg) < std::numeric_limits<double>::epsilon());
        
    result = max(42.0);
    assert(std::abs(result - 42.0) < std::numeric_limits<double>::epsilon());
    
    result = min(42.0);
    assert(std::abs(result - 42.0) < std::numeric_limits<double>::epsilon());
    
    result = sum(42.0);
    assert(std::abs(result - 42.0) < std::numeric_limits<double>::epsilon());
    
    result = average(42.0);
    assert(std::abs(result - 42.0) < std::numeric_limits<double>::epsilon());
    
    result = max(1, 2, 3, "test");
    assert(result == std::numeric_limits<double>::lowest());
    
    result = min(1, 2, 3, "test");
    assert(result == std::numeric_limits<double>::max());
    
    result = sum(1, 2, 3, "test");
    assert(std::abs(result) < std::numeric_limits<double>::epsilon());
    
    result = average(1, 2, 3, "test");
    assert(std::abs(result) < std::numeric_limits<double>::epsilon());
}

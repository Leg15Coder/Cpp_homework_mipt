#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <random>
#include <cmath>
#include <iterator>
#include <iomanip>


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
void print_range(std::string_view description, T range) {
    std::cout << std::setw(25) << std::left << description << ": [ ";
    for (const auto& value : range) {
        if constexpr (requires { value.first; value.second; }) {
            std::cout << "{" << value.first << ", " << value.second << "} ";
        } else {
            std::cout << value << " ";
        }
    }
    std::cout << "]" << std::endl;
}

namespace custom {

template<std::ranges::input_range InputRange, std::weakly_incrementable OutputIterator, typename UnaryPredicate, typename UnaryOperation>
OutputIterator transform_if(InputRange&& range, OutputIterator out, UnaryPredicate pred, UnaryOperation op) {
    auto view = range | std::views::filter(pred) | std::views::transform(op);
    return std::ranges::copy(view, out).out;
}

double calculate_mae(const std::vector<double>& y_true, const std::vector<double>& y_pred) {
    if (y_true.size() != y_pred.size() || y_true.empty()) {
        return 0.0;
    }
    double sum_abs_error = std::transform_reduce(
        y_true.cbegin(), y_true.cend(),
        y_pred.cbegin(),
        0.0,
        std::plus<>(),
        [](double true_val, double pred_val) {
            return std::abs(true_val - pred_val);
        }
    );
    return sum_abs_error / y_true.size();
}

double calculate_mse(const std::vector<double>& y_true, const std::vector<double>& y_pred) {
    if (y_true.size() != y_pred.size() || y_true.empty()) {
        return 0.0;
    }
    double sum_sq_error = std::transform_reduce(
        y_true.cbegin(), y_true.cend(),
        y_pred.cbegin(),
        0.0,
        std::plus<>(),
        [](double true_val, double pred_val) {
            double diff = true_val - pred_val;
            return diff * diff;
        }
    );
    return sum_sq_error / y_true.size();
}

}

void demo_ranges_algorithms() {
    std::vector<int> v_replace = {1, 2, 3, 1, 4, 1, 5};
    print_range("replace: before", v_replace);
    std::ranges::replace(v_replace, 1, 99);
    print_range("replace: after", v_replace);
    std::cout << std::endl;

    std::vector<int> v_fill = {0, 1, 2, 3, 4, 5, 6};
    print_range("fill: before", v_fill);
    std::ranges::fill(v_fill.begin() + 2, v_fill.end() - 2, -1);
    print_range("fill: after", v_fill);
    std::cout << std::endl;

    std::vector<int> v_unique = {1, 5, 2, 3, 5, 2, 1, 1, 3};
    print_range("unique: before sort", v_unique);
    std::ranges::sort(v_unique);
    print_range("unique: after sort", v_unique);
    auto ret = std::ranges::unique(v_unique);
    v_unique.erase(ret.begin(), ret.end());
    print_range("unique: after erase", v_unique);
    std::cout << std::endl;


    std::vector<int> v_rotate = {1, 2, 3, 4, 5, 6, 7};
    print_range("rotate: before", v_rotate);
    std::ranges::rotate(v_rotate, v_rotate.begin() + 3);
    print_range("rotate: after", v_rotate);
    std::cout << std::endl;

    std::vector<int> v_sample_src(20);
    std::iota(v_sample_src.begin(), v_sample_src.end(), 1);
    std::vector<int> v_sample_dest(5);
    std::mt19937 gen{std::random_device{}()};
    std::ranges::sample(v_sample_src, v_sample_dest.begin(), 5, gen);
    print_range("sample: source", v_sample_src);
    print_range("sample: destination", v_sample_dest);
}

void demo_views() {
    std::vector<int> v_views = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    print_range("views: source vector", v_views);
    std::cout << std::endl;

    auto even_view = v_views | std::views::filter([](int i) { return i % 2 == 0; });
    print_range("views::filter (even)", even_view);

    auto drop_view = v_views | std::views::drop(4);
    print_range("views::drop(4)", drop_view);

    auto stride_view = v_views | std::views::stride(3);
    print_range("views::stride(3)", stride_view);
    std::cout << std::endl;

    std::vector<std::vector<int>> vv_join = {{1, 2}, {3}, {4, 5, 6}};
    print_range("views::join: source", vv_join);
    auto join_view = vv_join | std::views::join;
    print_range("views::join: result", join_view);
    std::cout << std::endl;

    std::vector<std::string> v_zip_str = {"one", "two", "three", "four"};
    std::vector<int> v_zip_int = {1, 2, 3};
    print_range("views::zip: source 1", v_zip_str);
    print_range("views::zip: source 2", v_zip_int);
    auto zip_view = std::views::zip(v_zip_str, v_zip_int);
    print_range("views::zip: result", zip_view);
}

void demo_custom_algorithms() {
    std::vector<int> v_tif_src = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v_tif_dest;
    custom::transform_if(v_tif_src, std::back_inserter(v_tif_dest),
        [](int i){ return i % 2 == 0; },
        [](int i){ return i * 10; });
    print_range("transform_if: source", v_tif_src);
    print_range("transform_if: dest", v_tif_dest);
    std::cout << std::endl;

    std::vector<double> y_true = {1.0, 1.5, 2.0, 2.5, 3.0};
    std::vector<double> y_pred = {1.1, 1.4, 2.2, 2.7, 3.2};
    print_range("MAE/MSE: y_true", y_true);
    print_range("MAE/MSE: y_pred", y_pred);
    double mae = custom::calculate_mae(y_true, y_pred);
    double mse = custom::calculate_mse(y_true, y_pred);
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "MAE: " << mae << std::endl;
    std::cout << "MSE: " << mse << std::endl;
}


int main() {
    demo_ranges_algorithms();
    std::cout << std::endl;
    demo_views();
    std::cout << std::endl;
    demo_custom_algorithms();
    std::cout << std::endl;
}

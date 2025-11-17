#include <type_traits>
#include <vector>

template<typename T>
struct is_class {
private:
    template<typename U>
    static std::true_type test(int U::*);
    
    template<typename U>
    static std::false_type test(...);
    
public:
    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template<typename T>
inline constexpr bool is_class_v = is_class<T>::value;

template<typename T>
struct add_const {
    using type = const T;
};

template<typename T>
using add_const_t = typename add_const<T>::type;

template<typename T>
struct remove_const {
    using type = T;
};

template<typename T>
struct remove_const<const T> {
    using type = T;
};

template<typename T>
using remove_const_t = typename remove_const<T>::type;

template<bool B, typename T, typename F>
struct conditional;

template<typename T, typename F>
struct conditional<true, T, F> {
    using type = T;
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F;
};

template<bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

template<typename T>
struct remove_reference {
    using type = T;
};

template<typename T>
struct remove_reference <T&> {
    using type = T;
};

template<typename T>
struct remove_reference<T&&> {
    using type = T;
};

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename T>
using remove_cr_t = remove_reference_t<remove_const_t<T>>;

template<class T>
struct is_array : std::false_type {};
 
template<class T>
struct is_array<T[]> : std::true_type {};
 
template<class T, std::size_t N>
struct is_array<T[N]> : std::true_type {};

template< class T >
constexpr bool is_array_v = is_array<T>::value;

template<class T>
struct remove_extent { using type = T; };
 
template<class T>
struct remove_extent<T[]> { using type = T; };
 
template<class T, std::size_t N>
struct remove_extent<T[N]> { using type = T; };

template< class T >
using remove_extent_t = typename remove_extent<T>::type;

template<typename T>
struct decay {
private:
    using U = remove_reference_t<T>;
public:
    using type = conditional_t<
        is_array_v<U>,
        remove_extent_t<U>*,
        conditional_t<
            std::is_function_v<U>,
            std::add_pointer_t<U>,
            remove_cr_t<U>
        >
    >;
};

template<typename T>
using decay_t = typename decay<T>::type;

int main() {
    static_assert(is_class_v<std::vector<int>> == true);
    static_assert(is_class_v<int> == false);

    static_assert(std::is_same_v<add_const_t<int>, const int>);
    static_assert(std::is_same_v<add_const_t<std::vector<int>>, const std::vector<int>>);

    static_assert(std::is_same_v<remove_const_t<const int>, int>);
    static_assert(std::is_same_v<remove_const_t<int>, int>);

    static_assert(std::is_same_v<decay_t<const int&>, int>);
    static_assert(std::is_same_v<decay_t<int[10]>, int*>);

    static_assert(std::is_same_v<conditional_t<true, int, float>, int>);
    static_assert(std::is_same_v<conditional_t<false, int, float>, float>);
}

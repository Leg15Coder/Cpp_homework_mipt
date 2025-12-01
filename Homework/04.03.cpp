#include <vector>
#include <iostream>
#include <cassert>

template <typename Container, typename T>
void handle(Container&, T) {}

template <typename Container>
void handle(Container& container, int x) {
    container.push_back(x);
}

template<typename Container, typename... Args>
void push_back_all(Container& container, Args... args) {
    (handle(container, args), ...);
}

int main() {
    std::vector<int> vec;
    
    push_back_all(vec, 1, 3.4, 2, vec, 3, 'a', 4, 5);
    for (int i = 0; i < 5; ++i) assert(vec[i] == i + 1);
    assert(vec.size() == 5);
    assert(vec[0] == 1 && vec[4] == 5);
    
    push_back_all(vec, 3LL, 42);
    assert(vec.size() == 6);
    assert(vec[5] == 42);
    
    push_back_all(vec);
    for (int i = 0; i < 5; ++i) assert(vec[i] == i + 1);
    assert(vec[5] == 42);
    assert(vec.size() == 6);
    
    std::vector<int> vec2;
    vec2.reserve(10);
    push_back_all(vec2, 10, 'z', 20, 30);
    assert(vec2.size() == 3);
    assert(vec2[0] == 10 && vec2[2] == 30);
}

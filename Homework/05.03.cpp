#include <iostream>

class Slow {
public:
    void test() const {
        std::cout << "Slow::test\n";
    }
};

class Fast {
public:
    void test() const {
        std::cout << "Fast::test\n";
    }
};

template <typename Strategy>
class Entity : public Strategy {
public:
    void test() const {
        Strategy::test();
    }
};

int main() {
    Entity<Slow> entity1;
    entity1.test();

    Entity<Fast> entity2;
    entity2.test();
}

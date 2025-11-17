#include <string>
#include <cassert>

struct Person {
    std::string name;
    int age = 0;
    int grade = 0;
};


class Builder {
public:
    Builder() = default;

    Builder& name(const std::string& n) {
        m_person.name = n;
        return *this;
    }

    Builder& age(int a) {
        m_person.age = a;
        return *this;
    }

    Builder& grade(int g) {
        m_person.grade = g;
        return *this;
    }

    Person get() const {
        return m_person;
    }

private:
    Person m_person;
};


int main() {
    Builder builder;
    auto person = builder.name("Ivan").age(25).grade(10).get();

    static_assert(std::is_same_v<decltype(person), Person>);
    assert(person.name == "Ivan");
    assert(person.age == 25);
    assert(person.grade == 10);
}

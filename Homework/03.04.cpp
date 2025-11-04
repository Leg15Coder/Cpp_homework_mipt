#include <iostream>

class Tester1 {
private :
    friend class Client;
    Tester1() = default;
};

class Tester2 {
private :
    friend class Client;
    Tester2() = default;
};

class Entity
{
private :

    friend class Client;

    static void test(Tester1) { std::cout << "test 1\n"; }

    static void test(Tester2) { std::cout << "test 2\n"; }
};

class Client
{
public :

    static void test()
{
    Entity::test(Tester1());
    Entity::test(Tester2());
}
};

int main()
{
    Client::test();
}

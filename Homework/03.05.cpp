#include <iostream>
#include <string>


class Entity_v1 {
public:
    virtual ~Entity_v1() = default;
    
    virtual void test() {
        std::cout << "Entity_v1::test()" << std::endl;
    }
};


class Entity_v2 {
public:
    virtual ~Entity_v2() = default;
    
    virtual void test() {
        std::cout << "Entity_v2::test()" << std::endl;
    }
};


class Adapter_v1 : public Entity_v1 {
public:    
    void test() override final {
        test_v1();
    }
    
    virtual void test_v1() = 0;
};


class Adapter_v2 : public Entity_v2 {
public:    
    void test() override final {
        test_v2();
    }
    
    virtual void test_v2() = 0;
};


class Client : public Adapter_v1, public Adapter_v2 {
public:
    void test_v1() override {
        std::cout << "Client::test_v1()" << std::endl;
    }
    
    void test_v2() override {
        std::cout << "Client::test_v2()" << std::endl;
    }
};


int main() {
    Client client;
    
    Entity_v1* entity1 = &client;
    entity1->test();  // Вызывает Client::test_v1()
    
    Entity_v2* entity2 = &client;
    entity2->test();  // Вызывает Client::test_v2()
    
    Adapter_v1* adapter1 = &client;
    adapter1->test_v1();  // Вызывает Client::test_v1()
    
    Adapter_v2* adapter2 = &client;
    adapter2->test_v2();  // Вызывает Client::test_v2()
}

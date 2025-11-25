#include <iostream>

class Entity {
public:
    virtual ~Entity() = default;

    virtual void test() const = 0;
};

class Client : public Entity {
public:
    void test() const override {
        std::cout << "Client::test\n";
    }
};

class Server : public Entity {
public:
    void test() const override {
        std::cout << "Server::test\n";
    }
};

template <typename Base>
class Decorator : public Base {
public:
    void test() const override {
        std::cout << "Decorator::test : ";
        Base::test();
    }
};

int main() {
    Decorator<Client> entity_1;
    entity_1.test();

    Decorator<Server> entity_2;
    entity_2.test();
}

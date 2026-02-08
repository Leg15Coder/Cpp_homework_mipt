#include <iostream>

class Entity_v1 {
public:
    Entity_v1(int value) : private_field(value) {}

    void print() const {
        std::cout << "Entity_v1::private_field = " << private_field << std::endl;
    }

private:
    int private_field;
};

class Entity_v2 {
public:
    int public_field;
};

class Entity_v3 {
public:
    Entity_v3(int value) : private_data(value) {}

    void print() const {
        std::cout << "Entity_v3::private_data = " << private_data << std::endl;
    }

private:
    int private_data;
};

int main() {
    Entity_v1 entity1(1);
    entity1.print();

    Entity_v2& entity2 = reinterpret_cast<Entity_v2&>(entity1);
    entity2.public_field = 2;
    entity1.print();

    Entity_v3 simple_entity(3);
    simple_entity.print();

    int* fraudulent_ptr = reinterpret_cast<int*>(&simple_entity);
    *fraudulent_ptr = 4;
    simple_entity.print();
}

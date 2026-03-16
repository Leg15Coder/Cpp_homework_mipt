#include <memory>
#include <iostream>

////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  ------------------------------

    virtual void test() const = 0;
};

////////////////////////////////////////////////////

class Client : public Entity
{
public :
    void test() const override 
    { 
        std::cout << "Client::test\n";
    } 
};

////////////////////////////////////////////////////

class Server : public Entity
{
public :

    void test() const override 
    { 
        std::cout << "Server::test\n";
    }   
};

////////////////////////////////////////////////////

class Decorator : public Entity
{
public :

    Decorator(std::shared_ptr<Entity> entity) : m_entity(std::move(entity)) {}

//  ------------------------------------------------

    void test() const override
    { 
        std::cout << "Decorator::test : ";
        
        m_entity->test();
    }

private :

    std::shared_ptr<Entity> m_entity;
};

////////////////////////////////////////////////////

int main()
{
    auto entity_1 = std::make_shared<Client>();
    
    auto entity_2 = std::make_shared<Decorator>(entity_1);

//  ---------------------------------------------

    entity_2->test();
}

////////////////////////////////////////////////////
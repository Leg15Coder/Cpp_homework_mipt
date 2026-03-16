#include <memory>
#include <iostream>

/////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;
};

/////////////////////////////////////////////

class Client : public Entity {};

class Server : public Entity {};

/////////////////////////////////////////////

class Factory
{
public :

    virtual ~Factory() = default;

//  -----------------------------------------

    virtual std::unique_ptr<Entity> make_entity() const = 0;
};

/////////////////////////////////////////////

class Factory_Client : public Factory
{
public :

    std::unique_ptr<Entity> make_entity() const override
    {
        return std::make_unique<Client>();
    }
};

/////////////////////////////////////////////

class Factory_Server : public Factory
{
public :

    std::unique_ptr<Entity> make_entity() const override
    {
        return std::make_unique<Server>();
    }
};

/////////////////////////////////////////////

int main()
{

    std::unique_ptr<Factory> factory = std::make_unique<Factory_Client>();

//  ---------------------------------------

    std::unique_ptr<Entity> entity1 = factory->make_entity();

    factory = std::make_unique<Factory_Server>();
    std::unique_ptr<Entity> entity2 = factory->make_entity();
}

/////////////////////////////////////////////
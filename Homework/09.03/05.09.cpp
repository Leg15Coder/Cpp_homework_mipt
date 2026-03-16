#include <cassert>
#include <cstddef>
#include <vector>
#include <memory>
#include <iostream>

///////////////////////////////////////////////////////////////////////

class Entity
{
public :

    virtual ~Entity() = default;

//  -----------------------------

    virtual int test() const = 0;
};

///////////////////////////////////////////////////////////////////////

class Client : public Entity
{
public :

    int test() const override
    {
        return 1;
    }
};

///////////////////////////////////////////////////////////////////////

class Server : public Entity
{
public :

    int test() const override
    {
        return 2;
    }
};

///////////////////////////////////////////////////////////////////////

class Composite : public Entity
{
public :

    void add(std::unique_ptr<Entity> entity)
    {
        m_entities.push_back(std::move(entity));
    }

//  ------------------------------------

    int test() const override
    {
        auto x = 0;

        for (const auto& entity : m_entities)
        {
            if (entity)
            {
                x += entity->test();
            }
        }

        return x;
    }

private :

    std::vector<std::unique_ptr<Entity>> m_entities;
};

///////////////////////////////////////////////////////////////////////

auto make_composite(std::size_t size_1, std::size_t size_2) -> std::unique_ptr<Entity>
{
    auto composite = std::make_unique<Composite>();

    for (auto i = 0uz; i < size_1; ++i) {
        composite->add(std::make_unique<Client>());
    }

    for (auto i = 0uz; i < size_2; ++i) {
        composite->add(std::make_unique<Server>());
    }

    return composite;
}

///////////////////////////////////////////////////////////////////////

int main()
{
    auto composite = std::make_unique<Composite>();

//  -----------------------------------------

    for (auto i = 0uz; i < 5; ++i)
    {
        composite->add(make_composite(1, 1));
    }

//  -----------------------------------------

    assert(composite->test() == 15);

//  -----------------------------------------
}

///////////////////////////////////////////////////////////////////////
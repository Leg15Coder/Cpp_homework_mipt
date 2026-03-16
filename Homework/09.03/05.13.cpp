#include <iostream>
#include <vector>
#include <memory>

/////////////////////////////////////////////////

class Observer
{
public :

    virtual ~Observer() = default;

//  -----------------------------------

    virtual void test(int x) const = 0;
};

/////////////////////////////////////////////////

class Entity
{
public :

    void add(std::unique_ptr<Observer> observer)
    {
        m_observers.push_back(std::move(observer));
    }

//  ---------------------------------------

    void set(int x)
    {
        m_x = x;

        notify_all();
    }

//  ---------------------------------------

    void notify_all() const
    {
        for (const auto& observer : m_observers)
        {
            if (observer)
            {
                observer->test(m_x);
            }
        }
    }

private :

    int m_x = 0;

    std::vector<std::unique_ptr<Observer>> m_observers;
};

/////////////////////////////////////////////////

class Client : public Observer
{
public :

    void test(int x) const override
    {
        std::cout << "Client::test : x = " << x << "\n";
    }
};

/////////////////////////////////////////////////

class Server : public Observer
{
public :

    void test(int x) const override
    {
        std::cout << "Server::test : x = " << x << "\n";
    }
};

/////////////////////////////////////////////////

int main()
{
    Entity entity;

//  ----------------------------

    entity.add(std::make_unique<Client>());

    entity.add(std::make_unique<Server>());

//  ----------------------------

    for (auto i = 0; i < 2; ++i)
    {
        entity.set(i + 1);
    }
}

/////////////////////////////////////////////////
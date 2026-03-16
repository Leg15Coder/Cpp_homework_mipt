#include <iostream>
#include <memory>

/////////////////////////////////////////////////////////

class Strategy
{
public :

   virtual ~Strategy() = default;

//  ------------------------------

    virtual void test() const = 0;
};

/////////////////////////////////////////////////////////

class Client : public Strategy
{
public :

    void test() const override
    {
        std::cout << "Client::test\n";
    }
};

/////////////////////////////////////////////////////////

class Server : public Strategy
{
public :

    void test() const override
    {
        std::cout << "Server::test\n";
    }
};

/////////////////////////////////////////////////////////

class Entity
{
public :

    Entity(std::shared_ptr<Strategy> strategy) : m_strategy(std::move(strategy)) {}


//  -----------------------------------------------------

    void test() const
    {
        m_strategy->test();
    }

private :

    std::shared_ptr<Strategy> m_strategy;
};

/////////////////////////////////////////////////////////

int main()
{
    auto strategy = std::make_shared<Client>();

//  ---------------------------------

    Entity entity(strategy);

//  ---------------------------------

    entity.test();
}

/////////////////////////////////////////////////////////
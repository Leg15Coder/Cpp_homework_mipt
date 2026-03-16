#include <cassert>
#include <memory>
#include <iostream>

////////////////////////////////////////////////////

struct Entity
{
    int x = 0, y = 0;
};

////////////////////////////////////////////////////

class Builder
{
public :

    virtual ~Builder() = default;

//  -------------------------------

    auto make_entity()
    {
        m_entity = std::make_unique<Entity>();

        set_x();
        set_y();

        return std::move(m_entity);
    }

//  -------------------------------

    virtual void set_x() const = 0;
    virtual void set_y() const = 0;

protected :

    std::unique_ptr<Entity> m_entity = nullptr;
};

////////////////////////////////////////////////////

class Builder_Client : public Builder
{
public :

    void set_x() const override { m_entity->x = 1; }
    void set_y() const override { m_entity->y = 1; }
};

////////////////////////////////////////////////////

class Builder_Server : public Builder
{
public :

    void set_x() const override { m_entity->x = 2; }
    void set_y() const override { m_entity->y = 2; }
};

////////////////////////////////////////////////////

int main()
{
    std::unique_ptr<Builder> builder = std::make_unique<Builder_Client>();

    //  ---------------------------------------

    std::unique_ptr<Entity> client_entity = builder->make_entity();

    std::cout << "Client Entity: x=" << client_entity->x << ", y=" << client_entity->y << std::endl;
    assert(client_entity->x == 1);
    assert(client_entity->y == 1);

    builder = std::make_unique<Builder_Server>();
    std::unique_ptr<Entity> server_entity = builder->make_entity();
    std::cout << "Server Entity: x=" << server_entity->x << ", y=" << server_entity->y << std::endl;
    assert(server_entity->x == 2);
    assert(server_entity->y == 2);

    std::cout << "Exiting main." << std::endl;
}

////////////////////////////////////////////////////
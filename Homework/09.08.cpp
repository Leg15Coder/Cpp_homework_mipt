////////////////////////////////////////////////////////

#include <cstddef>
#include <new>
#include <print>

////////////////////////////////////////////////////////

template < typename D > class Entity
{
public :
    static auto operator new(std::size_t size) -> void *
    {
        std::print("Entity::operator new\n");

        return ::operator new(size);
    }

//  ----------------------------------------------------

    static void operator delete(void * x, std::size_t)
    {
        std::print("Entity::operator delete\n");

        ::operator delete(x);
    }

    static auto operator new[](std::size_t size) -> void *
    {
        std::print("Entity::operator new[]\n");

        return ::operator new[](size);
    }

    static void operator delete[](void * x, std::size_t)
    {
        std::print("Entity::operator delete[]\n");

        ::operator delete[](x);
    }

    static auto operator new(std::size_t size, const std::nothrow_t &) noexcept -> void *
    {
        std::print("Entity::operator new(nothrow)\n");

        return ::operator new(size, std::nothrow);
    }

    static void operator delete(void * x, const std::nothrow_t &) noexcept
    {
        std::print("Entity::operator delete(nothrow)\n");

        ::operator delete(x, std::nothrow);
    }

    static auto operator new[](std::size_t size, const std::nothrow_t &) noexcept -> void *
    {
        std::print("Entity::operator new[] (nothrow)\n");

        return ::operator new[](size, std::nothrow);
    }

    static void operator delete[](void * x, std::size_t size, const std::nothrow_t &) noexcept
    {
        std::print("Entity::operator delete[] (nothrow)\n");

        ::operator delete[](x, size, std::nothrow);
    }

protected :
    Entity() = default;

   ~Entity() = default;
};

////////////////////////////////////////////////////////

class Client : private Entity < Client >
{
private :

	using base_t = Entity < Client > ;

public :

	Client() { std::print("Client:: Client\n"); }

   ~Client() { std::print("Client::~Client\n"); }

//  ----------------------------------------------------

    using base_t::operator new, using base_t::operator delete;
    using base_t::operator new[], using base_t::operator delete[];
};

////////////////////////////////////////////////////////

int main()
{
    std::print("--- Testing single object ---
");
    Client* c1 = new Client;
    delete c1;

    std::print("--- Testing single object (nothrow) ---
");
    Client* c2 = new (std::nothrow) Client;
    if (c2) { // Always check for nullptr when using nothrow new
        delete c2;
    }

    std::print("--- Testing array objects ---
");
    Client* arr1 = new Client[3];
    delete[] arr1;

    std::print("--- Testing array objects (nothrow) ---
");
    Client* arr2 = new (std::nothrow) Client[3];
    if (arr2) { // Always check for nullptr when using nothrow new[]
        delete[] arr2;
    }

    return 0;
}

////////////////////////////////////////////////////////
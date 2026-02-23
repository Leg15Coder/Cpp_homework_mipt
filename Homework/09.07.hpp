#pragma once

#include <utility>
#include <boost/noncopyable.hpp>
#include <array>
#include <cstddef>
#include <new>
#include <bit>
#include <memory>

////////////////////////////////////////////////////////

class Entity : private boost::noncopyable
{
public :
    class Implementation;

    Entity();

    Entity(Entity && other) noexcept;

    ~Entity();

    auto & operator=(Entity && other) noexcept;

    void test() const;

    Implementation * get();

    const Implementation * get() const;

private :
    class Implementation
    {
    public:
        Implementation() { }
        
        ~Implementation() {  }

        void do_something() const { }

    private:
        char data[16];
    };

    alignas(std::max_align_t) std::array<std::byte, 16> m_storage;

    Implementation* get_impl_ptr() noexcept {
        return std::bit_cast<Implementation*>(m_storage.data());
    }

    const Implementation* get_impl_ptr() const noexcept {
        return std::bit_cast<const Implementation*>(m_storage.data());
    }
};

////////////////////////////////////////////////////////

inline Entity::Entity()
{
    static_assert(sizeof(Implementation) == m_storage.size());
    static_assert(alignof(Implementation) <= alignof(decltype(m_storage)));

    new (m_storage.data()) Implementation();
}

inline Entity::~Entity()
{
    std::destroy_at(get_impl_ptr());
}

inline Entity::Entity(Entity && other) noexcept
{
    static_assert(sizeof(Implementation) == m_storage.size());
    static_assert(alignof(Implementation) <= alignof(decltype(m_storage)));

    new (m_storage.data()) Implementation(std::move(*other.get_impl_ptr()));

    std::destroy_at(other.get_impl_ptr());
}

inline auto & Entity::operator=(Entity && other) noexcept
{
    if (this != &other)
    {
        std::destroy_at(get_impl_ptr());

        new (m_storage.data()) Implementation(std::move(*other.get_impl_ptr()));

        std::destroy_at(other.get_impl_ptr());
    }

    return *this;
}

inline void Entity::test() const
{
    get()->do_something();
}

inline Entity::Implementation * Entity::get()
{
    return std::launder(get_impl_ptr());
}

inline const Entity::Implementation * Entity::get() const
{
    return std::launder(get_impl_ptr());
}

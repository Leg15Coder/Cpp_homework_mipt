#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <print>
#include <utility>
#include <stdexcept>


class Vector
{
public :

	Vector() : m_array(nullptr), m_size(0), m_capacity(0) {}

	Vector(std::initializer_list < int > list) : m_size(std::size(list))
	{
        initialize_capacity();
        std::ranges::copy(list, m_array);
	}

	Vector(Vector const & other) : m_size(other.m_size)
	{
        initialize_capacity();
        std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
    }

	Vector(Vector && other)
	:
		m_array(std::exchange(other.m_array, nullptr)),
		m_size(std::exchange(other.m_size,  0)),
        m_capacity(std::exchange(other.m_capacity, 0)) {}

   ~Vector()
	{
		delete[] m_array;
	}

    void push_back(int x) {
        if (m_size == m_capacity) allocate();

        m_array[m_size++] = x;
    }

    int pop_back() {
        if (m_size == 0) throw std::out_of_range("Vector is empty");

        return m_array[--m_size];
    }

	auto & operator=(Vector other)
	{
		swap(other);
		return *this;
	}

	void swap(Vector & other)
	{
		std::swap(m_array, other.m_array);

		std::swap(m_size,  other.m_size);

        std::swap(m_capacity,  other.m_capacity);
	}

    std::size_t size() const {
        return m_size;
    }

    std::size_t capacity() const {
        return m_capacity;
    }

    void clear() {
        m_size = 0;
    }

    bool empty() const {
        return m_size == 0;
    }

private :

	int * m_array = nullptr;

	std::size_t m_size = 0;

    std::size_t m_capacity = 0;

    void allocate() {
        m_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        int* new_array = new int[m_capacity]{};
        
        std::ranges::copy(m_array, m_array + m_size, new_array);
        
        delete[] m_array;
        m_array = new_array;
    }

    void initialize_capacity() {
        m_capacity = 1;
        while (m_capacity <= m_size) m_capacity <<= 1;        

        m_array = new int[m_capacity]{};
    }
};


void swap(Vector & lhs, Vector & rhs)
{
	lhs.swap(rhs);
}


int main()
{
	Vector vector_1;

	Vector vector_2 = { 1, 2, 3, 4, 5 };

	Vector vector_3 = vector_2;

	Vector vector_4 = std::move(vector_3);

	vector_3 = vector_2;

	vector_4 = std::move(vector_3);

	swap(vector_1, vector_2);
}

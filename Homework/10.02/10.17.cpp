////////////////////////////////////////////////////////////////

#include <cassert>
#include <iterator>
#include <stack>

////////////////////////////////////////////////////////////////

template < typename T > class Stack
{
public :

    void push(T x)
    {
        if (std::empty(m_stack)) 
        {
            m_stack.push(x);
            m_min = x;
        }
        else if (x < m_min) 
        {
            m_stack.push(2 * x - m_min);
            m_min = x;
        }
        else 
        {
            m_stack.push(x);
        }
    }

//  ---------------------------------------------------------

    auto top() const
    {
        return m_stack.top() < m_min ? m_min : m_stack.top();
    }

//  ---------------------------------------------------------

    void pop()
    {
        if (auto t = m_stack.top(); t < m_min)
        {
            (m_min *= 2) -= t;
        }

        m_stack.pop();
    }

//  ---------------------------------------------------------
 
    auto min() const
    { 
        return m_min;
    }
 
private :

    std::stack < T > m_stack;
    
    T m_min = T();
};

////////////////////////////////////////////////////////////////

int main()
{
    Stack < int > stack;

    stack.push(2); assert(stack.top() == 2 && stack.min() == 2);

    stack.push(1); assert(stack.top() == 1 && stack.min() == 1);

    stack.push(3); assert(stack.top() == 3 && stack.min() == 1);

    stack.push(0); assert(stack.top() == 0 && stack.min() == 0);

//  ------------------------------------------------------------

                   assert(stack.top() == 0 && stack.min() == 0);

    stack.pop ( ); assert(stack.top() == 3 && stack.min() == 1);

    stack.pop ( ); assert(stack.top() == 1 && stack.min() == 1);

    stack.pop ( ); assert(stack.top() == 2 && stack.min() == 2);
    
    stack.pop ( );
}

////////////////////////////////////////////////////////////////
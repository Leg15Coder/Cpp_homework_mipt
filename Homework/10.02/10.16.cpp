////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <iterator>
#include <stack>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////////

template < typename T > class Stack
{
public :

    void push(T x)
    {
        m_stack.emplace(x, std::empty(m_stack) ? x : std::min(x, m_stack.top().second));
    }

//  ------------------------------------------------------------------------------------

    auto top() const
    { 
        return m_stack.top().first;
    }

//  ------------------------------------------------------------------------------------
 
    void pop() 
    { 
        m_stack.pop();
    }

//  ------------------------------------------------------------------------------------
 
    auto min() const
    { 
        return m_stack.top().second;
    }

private :

    std::stack < std::pair < T, T > > m_stack;
};

////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////

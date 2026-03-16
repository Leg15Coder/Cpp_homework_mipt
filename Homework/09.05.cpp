#include <iterator>
#include <memory>

///////////////////////////////////////////////////////////////////////////////////

template < typename T > class List
{
private :

		struct Node
		{
			T x;
			std::shared_ptr < Node > next;
			std::weak_ptr < Node > prev;
	
			Node(T val, std::shared_ptr<Node> next_node, std::weak_ptr<Node> prev_node)
			    : x(val), next(next_node), prev(prev_node) {}
		};	
public :

	class Iterator
	{
	public :

		using iterator_category = std::bidirectional_iterator_tag;

	//  -------------------------------------------------------------------

		Iterator(std::shared_ptr < Node > node = nullptr) : m_node(node) {}

	//  -------------------------------------------------------------------

		auto const operator++(int)
		{
			auto x = *this;

			m_node = m_node->next;

			return x;
		}

	//  -------------------------------------------------------------------

		auto & operator++()
		{
			m_node = m_node->next;

			return *this;
		}

	//  -------------------------------------------------------------------

		auto & operator--()
		{
			m_node = m_node->prev.lock();

			return *this;
		}

	//  -------------------------------------------------------------------

		auto const operator--(int)
		{
			auto x = *this;

			m_node = m_node->prev.lock();

			return x;
		}

	//  -------------------------------------------------------------------

		auto & operator* () const { return  m_node->x; }

		auto   operator->() const { return &m_node->x; }

	//  -------------------------------------------------------------------

		friend auto operator==(Iterator const & lhs, Iterator const & rhs)
		{
			return lhs.m_node == rhs.m_node;
		}

	private :

		std::shared_ptr < Node > m_node;
	};

//  -----------------------------------------------------------------------

	auto begin() const { return Iterator(m_head); }

	auto end  () const { return Iterator(      ); }

//  -----------------------------------------------------------------------

		void push_back(T x)
		{
			auto new_node = std::make_shared < Node > (x, nullptr, std::weak_ptr<Node>());
	
			if (m_head)
			{
				auto tail = m_head;

				while (tail->next)
				{
					tail = tail->next;
				}

				new_node->prev = tail;
				
				tail->next = new_node;
			}
			else
			{
				m_head = new_node;
			}
		}
private :

	std::shared_ptr < Node > m_head;
};

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	List < int > list;

//  -------------------------------------------------------------------------------

	list.push_back(1);

//  -------------------------------------------------------------------------------

	for (auto iterator = std::begin(list); iterator != std::end(list); ++iterator);

//  -------------------------------------------------------------------------------

	for ([[maybe_unused]] auto element : list);
}

///////////////////////////////////////////////////////////////////////////////////
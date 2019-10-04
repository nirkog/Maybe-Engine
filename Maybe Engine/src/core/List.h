#pragma once

#include <memory>
#include <iostream>

#include "Allocator.h"
#include "StdAllocator.h"
#include "PoolAllocator.h"
#include "Sort.h"

namespace mb {

	template<typename T>
	class List
	{
	public:
		struct Node {
			Node* prev;
			Node* next;
			T value;
		};

		class Iterator
		{
		public:
			Iterator(Node* node)
				: m_Node(node)
			{

			}

			Iterator()
				: m_Node(nullptr)
			{

			}

			Iterator& operator++()
			{
				m_Node = m_Node->next;

				return *this;
			}

			Iterator& operator--()
			{
				m_Node = m_Node->prev;

				return *this;
			}

			Iterator operator++(int)
			{
				Iterator result = *this;
				m_Node = m_Node->next;

				return result;
			}

			Iterator operator--(int)
			{
				Iterator result = *this;
				m_Node = m_Node->prev;

				return result;
			}

			Iterator& operator+=(int offset)
			{
				if (offset > 0)
					for (int i = 0; i < offset; i++) m_Node = m_Node->next;
				else
					for (int i = 0; i > offset; i--) m_Node = m_Node->prev;
				
				return *this;
			}

			Iterator& operator-=(int offset)
			{
				if (offset > 0)
					for (int i = 0; i < offset; i++) m_Node = m_Node->prev;
				else
					for (int i = 0; i > offset; i--) m_Node = m_Node->next;

				return *this;
			}

			Iterator operator+(int offset)
			{
				Iterator result = *this;

				if (offset > 0)
					for (int i = 0; i < offset; i++) result++;
				else
					for (int i = 0; i > offset; i--) result--;

				return result;
			}

			Iterator operator-(int offset)
			{
				Iterator result = *this;

				if (offset > 0)
					for (int i = 0; i < offset; i++) result--;
				else
					for (int i = 0; i > offset; i--) result++;

				return result;
			}

			bool operator==(const Iterator& other)
			{
				if (m_Node == other._GetNode())
					return true;

				return false;
			}

			bool operator!=(const Iterator& other)
			{
				if (m_Node != other._GetNode())
					return true;

				return false;
			}

			T& operator*()
			{
				return m_Node->value;
			}

			Node* _GetNode() const { return m_Node; }
		private:
			Node* m_Node;
		};

	public:
		List(Allocator<Node>* allocator=nullptr)
			: m_Start(nullptr), m_End(nullptr), m_Count(0)
		{
			if (allocator == nullptr)
				m_Allocator = StdAllocator<Node>::GetInstance();
			else
				m_Allocator = allocator;

			m_End = m_Allocator->Allocate(1);
			m_Start = m_End;

			m_End->next = nullptr;
			m_Start->prev = nullptr;
		}

		~List()
		{
			Node* cur = m_Start;

			while (cur != nullptr)
			{
				Node* next = cur->next;
				m_Allocator->Free(cur, 1);
				cur = next;
			}
		}

		Iterator Begin() const { return Iterator(m_Start); }
		Iterator End() const { return Iterator(m_End); }

		T Front() const { return m_Start->value; }
		T Back() const { return m_End->prev->value; }

		unsigned int Count() { return m_Count; }

		void PushBack(const T& value)
		{
			if (m_Count == 0)
			{
				m_Start = m_Allocator->Allocate(1);

				m_Start->value = value;

				m_Start->next = m_End;
				m_Start->prev = nullptr;

				m_End->prev = m_Start;
			}
			else
			{
				Node* node = m_Allocator->Allocate(1);

				node->next = m_End;
				node->prev = m_End->prev;

				node->value = value;

				m_End->prev->next = node;
				m_End->prev = node;
			}

			m_Count++;
		}

		void PushFront(const T& value)
		{
			if (m_Count == 0)
			{
				m_Start = m_Allocator->Allocate(1);

				m_Start->value = value;

				m_Start->next = m_End;
				m_Start->prev = nullptr;

				m_End->prev = m_Start;
			}
			else
			{
				Node* node = m_Allocator->Allocate(1);

				node->prev = nullptr;
				node->next = m_Start;

				node->value = value;

				m_Start->prev = node;
				m_Start = node;
			}

			m_Count++;
		}

		void Insert(Iterator iterator, const T& value)
		{
			if (iterator._GetNode() != nullptr)
			{
				if (iterator._GetNode() == m_End)
				{
					PushBack(value);
				}
				else if (iterator._GetNode() == m_Start)
				{
					PushFront(value);
				}
				else
				{
					Node* node = m_Allocator->Allocate(1);

					node->value = value;

					node->next = iterator._GetNode();
					node->prev = iterator._GetNode()->prev;

					iterator._GetNode()->prev->next = node;
					iterator._GetNode()->prev = node;

					m_Count++;
				}
			}
		}

		T PopBack()
		{
			T value = (T) NULL;

			if (m_Count != 0)
			{
				if (m_Count == 1)
				{
					value = m_Start->value;

					m_Allocator->Free(m_Start, 1);
					
					m_Start = m_End;

					m_Start->prev = nullptr;
				}
				else
				{
					Node* node = m_End->prev;
					value = m_End->prev->value;

					node->prev->next = m_End;
					m_End->prev = node->prev;
					
					m_Allocator->Free(node, 1);
				}

				m_Count--;
			}

			return value;
		}

		T PopFront()
		{
			T value = (T) NULL;

			if (m_Count != 0)
			{
				if (m_Count == 1)
				{
					value = m_Start->value;

					m_Allocator->Free(m_Start, 1);

					m_Start = m_End;

					m_Start->prev = nullptr;
				}
				else
				{
					Node* node = m_Start;
					value = node->value;

					m_Start = node->next;
					node->next->prev = nullptr;

					m_Allocator->Free(node, 1);
				}

				m_Count--;
			}

			return value;
		}

		Iterator Erase(Iterator iterator)
		{
			Iterator result(nullptr);

			if (iterator._GetNode() != nullptr && iterator._GetNode() != m_End)
			{
				if (iterator._GetNode() == m_Start)
				{
					PopFront();
					iterator = Iterator(m_Start);
				}
				else if (iterator._GetNode() == m_End->prev)
				{
					PopBack();
					iterator = Iterator(m_End->prev);
				}
				else
				{
					Node* node = iterator._GetNode();
					result = node->next;

					node->prev->next = node->next;
					node->next->prev = node->prev;

					m_Allocator->Free(node, 1);

					m_Count--;
				}
			}

			return result;
		}

		Iterator Erase(Iterator start, Iterator end)
		{
			if (start._GetNode() != nullptr && end._GetNode() != nullptr && start._GetNode() != m_End && end._GetNode() != m_End)
			{
				Node* startNode = start._GetNode();
				Node* endNode = end._GetNode();

				Node* left = startNode->prev;
				Node* right = endNode;

				Node* cur = startNode;
				Node* next;

				unsigned int diff = 0;
				while (cur != endNode)
				{
					next = cur->next;
					m_Allocator->Free(cur, 1);
					cur = next;
					
					diff++;
				}

				left->next = right;
				right->prev = left;

				m_Count -= diff;
			}

			return end;
		}

		void Clear()
		{
			Node* cur = m_Start;

			while (cur != m_End)
			{
				Node* next = cur->next;
				m_Allocator->Free(cur, 1);
				cur = next;
			}

			m_End->prev = nullptr;
			m_Start = m_End;

			m_Count = 0;
		}

		void Remove(T value)
		{
			Node* cur = m_Start;
			Node* next = nullptr;

			while (cur->next != nullptr)
			{
				next = cur->next;
				if (cur->value == value) Erase(Iterator(cur));
				cur = next;
			}
		}

		void RemoveIf(bool (*comparator)(const T&), bool toRemove=true)
		{
			Node* cur = m_Start;
			Node* next = nullptr;

			while (cur->next != nullptr)
			{
				next = cur->next;
				if (comparator(cur->value) == toRemove) Erase(Iterator(cur));
				cur = next;
			}
		}

		void Sort(bool (*comparator)(const T&, const T&))
		{
			Node* i, *j;
			T key;

			for (i = m_Start->next; i != m_End; i = i->next)
			{
				key = i->value;
				j = i->prev;

				while (j != nullptr && comparator(key, j->value))
				{
					j->next->value = j->value;
					j = j->prev;
				}

				if (j != nullptr) j->next->value = key;
				else m_Start->value = key;
			}
		}

		Node* First() { return m_Start; }

	private:
		Node* m_Start;
		Node* m_End;

		unsigned int m_Count;

		Allocator<Node>* m_Allocator;
	};
}
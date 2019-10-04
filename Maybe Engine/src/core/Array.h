#pragma once

#include <memory>

#include "Allocator.h"
#include "StdAllocator.h"
#include "Sort.h"

namespace mb {

	template<typename T>
	class Array
	{
	public:
		class Iterator
		{
		public:
			Iterator()
				: m_Element(nullptr)
			{

			}

			Iterator(T* element)
				: m_Element(element)
			{

			}

			Iterator& operator++()
			{
				m_Element++;

				return *this;
			}

			Iterator& operator--()
			{
				m_Element--;

				return *this;
			}

			Iterator operator++(int)
			{
				Iterator result = *this;
				m_Element++;

				return result;
			}

			Iterator operator--(int)
			{
				Iterator result = *this;
				m_Element--;

				return result;
			}

			Iterator& operator+=(int offset)
			{
				m_Element += offset;

				return *this;
			}

			Iterator& operator-=(int offset)
			{
				m_Element -= offset;

				return *this;
			}

			Iterator operator+(int offset)
			{
				Iterator result(m_Element + offset);
				
				return result;
			}

			Iterator operator-(int offset)
			{
				Iterator result(m_Element - offset);

				return result;
			}

			bool operator==(const Iterator& other)
			{
				if (m_Element == other._GetElement())
					return true;

				return false;
			}

			bool operator!=(const Iterator& other)
			{
				if (m_Element != other._GetElement())
					return true;

				return false;
			}

			T& operator*()
			{
				return *m_Element;
			}

			T* _GetElement() inline const { return m_Element; };
		private:
			T* m_Element;
		};
	public:
		Array(Allocator<T>* allocator=nullptr, unsigned int capacity=2)
			: m_Capacity(capacity), m_Count(0)
		{
			if (allocator == nullptr)
				m_Allocator = StdAllocator<T>::GetInstance();
			else
				m_Allocator = allocator;

			m_Array = m_Allocator->Allocate(m_Capacity);
		}

		const unsigned int Count() inline const { return m_Count; }
		const unsigned int Capacity() inline const { return m_Capacity; }
		T* GetAddress() inline const { return m_Array; }

		Iterator Begin() inline const { return Iterator(&m_Array[0]); }
		Iterator End() inline const { return Iterator(&m_Array[m_Count]); }

		void Resize(unsigned int capacity)
		{
			unsigned int oldCapacity = m_Capacity;
			m_Capacity = capacity;
			
			T* newAddress = m_Allocator->Allocate(m_Capacity);

			memcpy(newAddress, m_Array, m_Count * sizeof(T));

			m_Allocator->Free(m_Array, oldCapacity);

			m_Array = newAddress;
		}

		const T& PushBack(const T& value)
		{
			if (m_Count == m_Capacity) Resize(m_Capacity * 2);

			m_Array[m_Count] = value;

			m_Count++;
		
			return m_Array[m_Count];
		}

		const T Erase(const Iterator& iterator) 
		{
			T returnValue = *iterator._GetElement();

			m_Count--;

			for (Iterator it = iterator, end = End(); it != end; it++) *it = *(it + 1);

			return returnValue;
		}

		const T Erase(const Iterator& start, const Iterator& end)
		{
			T returnValue = *end._GetElement();

			unsigned int diff = 0;
			for (Iterator it = start; it != end; it++) diff++;

			m_Count -= diff;

			for (Iterator it = start, endIt = End(); it != endIt; it++) *it = (*it + diff);

			return returnValue;
		}

		void Clear()
		{
			memset(m_Array, NULL, m_Count * sizeof(T));

			m_Count = 0;
		}

		void Reserve(unsigned int capacity)
		{
			Resize(capacity);
		}

		void ShrinkToFit()
		{
			Resize(m_Count);
		}

		void Sort()
		{
			SortAlgorithms<T>::QuickSort(m_Array, m_Count);
		}

		void Sort(bool reverse)
		{
			SortAlgorithms<T>::QuickSort(m_Array, m_Count, reverse ? Comparators<T>::DefaultReverse : Comparators<T>::Default);
		}

		void Sort(bool (*comparator)(const T&, const T&))
		{
			SortAlgorithms<T>::QuickSort(m_Array, m_Count, comparator);
		}

		T& Get(unsigned int index) inline const
		{
			return m_Array[index];
		}

		T& operator[](unsigned int index) const 
		{
			return Get(index);
		}

		Array<T>& operator=(const Array<T>& other)
		{
			m_Allocator->Free(m_Array, m_Capacity);

			m_Count = other.Count();
			m_Capacity = other.Capacity();

			m_Array = m_Allocator->Allocate(m_Capacity);

			for (unsigned int i = 0; i < m_Count; i++)
				m_Array[i] = other[i];
			
			return *this;
		}

		~Array()
		{
			m_Allocator->Free(m_Array, m_Capacity);
		}
	private:
		T* m_Array;
		unsigned int m_Count, m_Capacity;
		Allocator<T>* m_Allocator;
	};

}
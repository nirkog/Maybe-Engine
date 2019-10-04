#pragma once

#include <memory>

#include "Allocator.h"

namespace mb {

	template<typename T>
	class StdAllocator : public Allocator<T>
	{
	private:
		StdAllocator()
		{

		}
	public:
		T* Allocate(unsigned int count)
		{
			return m_Allocator.allocate(count);
		}

		void Free(T* block, unsigned int count)
		{
			m_Allocator.deallocate(block, count);
		}

		void PrintFreeAdresses()
		{

		}

		static StdAllocator<T>* GetInstance()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new StdAllocator<T>();
			}
			
			return m_Instance;
		}
	private:
		std::allocator<T> m_Allocator;

		static StdAllocator<T>* m_Instance;
	};


	template<typename T>
	StdAllocator<T>* StdAllocator<T>::m_Instance = nullptr;

}
#pragma once

#include <memory>
#include <iostream>

#include "Allocator.h"

namespace mb {

	template<typename T>
	class PoolAllocator : public Allocator<T>
	{
	public:
		PoolAllocator(unsigned int count)
			: m_Size(sizeof(T) * count), m_Count(count), m_FreeBlocks(count)
		{
			if (sizeof(T) < sizeof(void*)) std::cout << "Problem!" << std::endl;

			m_Start = (char*) malloc(m_Size);
			memset(m_Start, 0, m_Size);
			m_First = m_Start;

			for (unsigned int i = 0; i < m_Count - 1; i++)
			{
				void** block = (void**) (m_Start + i * sizeof(T));
				*(block) = m_Start + (i + 1) * sizeof(T);
			}

			void** lastBlock = (void**) (m_Start + (m_Count - 1) * sizeof(T));
			*(lastBlock) = nullptr;
		}

		~PoolAllocator()
		{
			free(m_Start);
		}

		// Return capacity in count of elements
		unsigned int Capacity() inline const { return m_Count; }

		// Return the amount of free blocks left to allocate
		unsigned int FreeBlocksLeft() inline const { return m_FreeBlocks; }

		T* Allocate(unsigned int count)
		{
			if (m_First != nullptr && count <= m_FreeBlocks)
			{
				if (count != 0)
				{
					void* block = m_First;

					//PrintFreeAdresses();

					for(unsigned int i = 0; i < count; i++) m_First = *((void**) m_First);

					m_FreeBlocks -= count;

					//PrintFreeAdresses();

					return (T*) block;
				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				std::cout << "Pool allocator is out of memory!" << std::endl;

				return nullptr;
			}
		}

		void Free(T* block, unsigned int count)
		{
			memset(block, 0, sizeof(T) * count);

			// !!!!Reverse the order of freeing the block so that the first block would be the first block in the array freed
			//for (unsigned int i = 0; i < count - 1; i++, block++);

			//PrintFreeAdresses();

			for (unsigned int i = 0; i < count; i++, block++)
			{
				void* oldFirst = m_First;

				m_First = block;
				void** freeBlock = (void**) block;
				*(freeBlock) = oldFirst;

				//std::cout << m_First << "(" << *((void**) m_First) << ")" << " -> " << oldFirst << std::endl;
			}

			//PrintFreeAdresses();

			m_FreeBlocks += count;
		}

		void PrintFreeAdresses()
		{
			void* block = m_First;

			if (block == nullptr) std::cout << "Allocator is out of free blocks!" << std::endl;

			while (block != nullptr)
			{
				std::cout << block;
				block = *((void**) block);

				if (block != nullptr) std::cout << " -> ";
				else std::cout << std::endl;
			}
		}
	private:
		char* m_Start;
		void* m_First;
		unsigned int m_Size, m_Count, m_FreeBlocks;
	};
	
}
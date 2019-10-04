#include "StackAllocator.h"

#include <iostream>

namespace mb {

	StackAllocator::StackAllocator(unsigned int capacity)
		: m_Capacity(capacity), m_Offset(0)
	{
		m_Start = (char*) malloc(m_Capacity);

		memset(m_Start, NULL, m_Capacity);

		std::cout << "Hi";
	}

	StackAllocator::~StackAllocator()
	{
		free(m_Start);
	}

	void* StackAllocator::Allocate(unsigned int size)
	{
		if (size + m_Offset > m_Capacity)
			return nullptr;

		void* block = m_Start + m_Offset;

		m_Offset += size;

		return block;
	}

	void StackAllocator::Free()
	{
		memset(m_Start, NULL, m_Offset);
		m_Offset = 0;
	}
}
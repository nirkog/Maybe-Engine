#pragma once

#include <memory>

namespace mb {

	class StackAllocator
	{
	public:
		StackAllocator(unsigned int capacity = 32);
		~StackAllocator();
		
		void* Allocate(unsigned int size);

		void* GetStartAdress() const { return (void*) m_Start; };
		void* GetCurrentAdress() const { return (void*) (m_Start + m_Offset); }

		void Free();
	private:
		char* m_Start;
		unsigned int m_Capacity, m_Offset;
	};

}
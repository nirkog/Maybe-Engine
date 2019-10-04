#pragma once

#include "StackAllocator.h"

namespace mb {

	class DoubleBufferedStackAllocator
	{
	public:
		DoubleBufferedStackAllocator(unsigned int m_Capacity)
			: m_Front(m_Capacity), m_Back(m_Capacity), m_CurrentBuffer(&m_Front)
		{

		}

		void SwapBuffers()
		{
			m_CurrentBuffer = m_CurrentBuffer == &m_Front ? &m_Back : &m_Front;
		}

		void FreeCurrentBuffer()
		{
			m_CurrentBuffer->Free();
		}

		void* Allocate(unsigned int size)
		{
			return m_CurrentBuffer->Allocate(size);
		}
	private:
		StackAllocator* m_CurrentBuffer;
		StackAllocator m_Front, m_Back;
	};

}
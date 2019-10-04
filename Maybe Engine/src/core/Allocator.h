#pragma once

namespace mb {

	template<typename T>
	class Allocator
	{
	public:
		virtual T* Allocate(unsigned int count) = 0;
		virtual void Free(T* block, unsigned int count) = 0;

		virtual void PrintFreeAdresses() = 0;
	};

}
#pragma once

#include "core/List.h"
#include "Layer.h"

namespace mb
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void RemoveLayer(Layer* layer);

		inline unsigned int GetCount() const { return m_Count; }

		List<Layer*>::Iterator Begin() const { return m_Stack.Begin(); }
		List<Layer*>::Iterator End() const { return m_Stack.End(); }
	private:
		List<Layer*> m_Stack;
		unsigned int m_Count;
	};
}
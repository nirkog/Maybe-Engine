#include "LayerStack.h"

namespace mb
{
	LayerStack::LayerStack()
		: m_Count(0)
	{

	}

	LayerStack::~LayerStack()
	{
		for (List<Layer*>::Iterator it = m_Stack.Begin(), end = m_Stack.End(); it != end; it++)
		{
			m_Count--;
			(*it)->OnDetach();

			delete (*it);
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Stack.PushFront(layer);

		layer->OnAttach();

		m_Count++;
	}

	void LayerStack::RemoveLayer(Layer* layer)
	{
		layer->OnDetach();

		m_Stack.Remove(layer);
		m_Count--;
	}
}
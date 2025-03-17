#pragma once

#include "Layer.h"

namespace PathTracing
{

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		template<typename T>
		void pushLayer()
		{
			Layer* layer = new T();
			m_layerStack.emplace(m_layerStack.begin() + m_currentLayerPushIndex, layer);
			layer->onAttach();
		}
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_layerStack.begin(); }
		std::vector<Layer*>::iterator end() { return m_layerStack.end(); }

	private:
		std::vector<Layer*> m_layerStack;
		uint32_t m_currentLayerPushIndex = 0;
	};

}
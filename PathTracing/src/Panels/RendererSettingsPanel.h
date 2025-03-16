#pragma once

namespace PathTracing
{

	class RendererSettingsPanel
	{
	public:
		RendererSettingsPanel() = default;

		void onUpdate(float delta);

		void onGuiRender();

	private:
		float m_deltaTime;
	};

}
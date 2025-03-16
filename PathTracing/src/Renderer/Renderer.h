#pragma once

namespace PathTracing
{

	class Renderer
	{
	public:
		Renderer();

		void onResize(uint32_t width, uint32_t height);

		void Render();

	private:

	};

}
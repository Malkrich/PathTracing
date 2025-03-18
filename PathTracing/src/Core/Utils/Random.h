#pragma once

namespace PathTracing
{

	class Random
	{
	public:
		static float randomFloat();
		static float range(float min, float max);
		static glm::vec3 unitSphereVector();
	};

}
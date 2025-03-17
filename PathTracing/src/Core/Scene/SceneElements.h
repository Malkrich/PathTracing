#pragma once

#include <glm/glm.hpp>

namespace PathTracing
{

	struct Sphere
	{
		glm::vec3 Position{ 0.0f };
		float Radius = 0.5f;

		Sphere() = default;
	};

}
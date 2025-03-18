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

	struct Plane
	{
		glm::vec3 Position{ 0.0f };
		glm::vec3 Normal{ 0.0f, 1.0f, 0.0f };
		//glm::vec2 Size = { 1.0f, 1.0f };

		Plane() = default;
	};

	struct DirectionalLight
	{
		glm::vec3 Direction = { -1.0f, 0.0f, 0.0 };
	};

	struct Material
	{
		glm::vec3 Albedo = { 1.0f, 1.0f, 1.0f };
	};

}
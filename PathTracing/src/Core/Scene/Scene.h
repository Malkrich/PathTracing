#pragma once

#include "SceneElements.h"

#include <vector>

namespace PathTracing
{

	enum class ObjectType
	{
		None = 0,
		Sphere,
		Plane
	};

	struct Scene
	{
		DirectionalLight DirectionalLight;
		std::vector<Sphere> Spheres = {};
		std::vector<Material> SphereMaterials = {};
		std::vector<Plane> Planes = {};
		std::vector<Material> PlaneMaterials = {};

		const Material& getMaterial(ObjectType object, uint32_t index) const;

		void addSphere(const Sphere& sphere, const Material& material);
		void addPlane(const Plane& plane, const Material& material);
	};

}
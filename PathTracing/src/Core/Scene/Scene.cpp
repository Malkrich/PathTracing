#include "Pch.h"

#include "Core/Base.h"
#include "Scene.h"

namespace PathTracing
{

	const Material& Scene::getMaterial(ObjectType object, uint32_t index) const
	{
		PT_ASSERT(object != ObjectType::None, "Object type is unknown!");

		switch (object)
		{
			case ObjectType::Sphere:
				return SphereMaterials[index];
			case ObjectType::Plane:
				return PlaneMaterials[index];
		}
	}

	void Scene::addSphere(const Sphere& sphere, const Material& material)
	{
		Spheres.push_back(sphere);
		SphereMaterials.push_back(material);
	}

	void Scene::addPlane(const Plane& plane, const Material& material)
	{
		Planes.push_back(plane);
		PlaneMaterials.push_back(material);
	}

}
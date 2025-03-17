#include "Pch.h"

#include "Scene.h"

namespace PathTracing
{

	void Scene::addSphere(const Sphere& sphere, const Material& material)
	{
		m_spheres.push_back(sphere);
		m_sphereMaterials.push_back(material);
	}

}
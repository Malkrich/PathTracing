#pragma once

#include "SceneElements.h"

#include <vector>

namespace PathTracing
{

	struct Scene
	{
	public:
		Scene() = default;

		const std::vector<Sphere>& getSpheres() const { return m_spheres; }
		const std::vector<Material>& getSphereMaterials() const { return m_sphereMaterials; }

		void addSphere(const Sphere& sphere, const Material& material);

	private:
		DirectionalLight m_directionalLight;
		std::vector<Sphere> m_spheres = {};
		std::vector<Material> m_sphereMaterials = {};
	};

}
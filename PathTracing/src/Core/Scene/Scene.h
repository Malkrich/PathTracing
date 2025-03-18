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
		const std::vector<Plane>& getPlanes() const { return m_planes; }
		const std::vector<Material>& getSphereMaterials() const { return m_sphereMaterials; }
		const std::vector<Material>& getPlaneMaterials() const { return m_planeMaterials; }

		void addSphere(const Sphere& sphere, const Material& material);
		void addPlane(const Plane& plane, const Material& material);

	private:
		DirectionalLight m_directionalLight;
		std::vector<Sphere> m_spheres = {};
		std::vector<Material> m_sphereMaterials = {};
		std::vector<Plane> m_planes = {};
		std::vector<Material> m_planeMaterials = {};
	};

}
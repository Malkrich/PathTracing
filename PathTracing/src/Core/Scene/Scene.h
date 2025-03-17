#pragma once

#include "SceneElements.h"

#include <vector>

namespace PathTracing
{

	struct Scene
	{
		std::vector<Sphere> Spheres = {};

		Scene() = default;
	};

}
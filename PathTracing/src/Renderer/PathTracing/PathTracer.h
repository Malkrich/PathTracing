#pragma once

#include <memory>

#include "Renderer/Camera.h"
#include "Renderer/Image.h"
#include "Renderer/Scene/Scene.h"

namespace PathTracing
{

//static glm::vec3 threshold1(glm::vec3);

class PathTracer
{
public:
    static void pathTrace(std::shared_ptr<Image> image, std::shared_ptr<Scene> scene);

    static Ray ray_generator(const Camera& cam, float u, float v);
    static bool compute_intersection(const Ray& r, const Scene& scene, IntersectData& intersection, int& index_intersected_primitive);
    static glm::vec3 getValue(const Ray& r, const Scene& scene);
};

}

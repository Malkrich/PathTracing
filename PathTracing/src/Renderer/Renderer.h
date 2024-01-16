#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Image.h"
#include "PathTracing/Ray.h"
#include "Renderer/Scene/Scene.h"
#include "Renderer/Primitives/IntersectData.h"
#include "Camera.h"
#include "PathTracing/Ray.h"

namespace PathTracing
{

class Renderer
{
public:
    static void init();
    static void shutdown();

    static unsigned int getViewportWidth();
    static unsigned int getViewportHeight();

    static void begin(const glm::vec3& clearColor);
    static void pathTrace(std::shared_ptr<Image> image, std::shared_ptr<Scene> scene);
    static void draw(const std::shared_ptr<Image>& image);
    static void resize(unsigned int width, unsigned int height);

    static Ray ray_generator(const Camera& cam,float u,float v);
    static bool compute_intersection(const Ray& r, const Scene& scene, IntersectData& intersection, int& index_intersected_primitive);
    static glm::vec3 getValue(const Ray& r, const Scene& scene);
};

}

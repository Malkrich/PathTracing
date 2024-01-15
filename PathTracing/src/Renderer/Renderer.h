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

    static void pathTrace(); // TODO : pass a scene as parameter here : "pathTrace(scene);"
    static void draw();


    static Ray ray_generator(Camera const& cam,float const u,float const v);
    static bool compute_intersection(Ray const& r,Scene const& scene,IntersectData& intersection,int& index_intersected_primitive);
    static glm::vec3 getValue(Ray const& r, const Scene& scene);
};

}

#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "PathTracing/Ray.h"
#include "PathTracing/Scene/Scene.h"
#include "PathTracing/Primitives/IntersectData.h"
#include "PathTracing/Camera.h"
#include "PathTracing/Ray.h"

namespace PathTracing
{

class Renderer
{
public:
    static void init();
    static void shutdown();

    static void begin(const glm::vec3& clearColor);
    static void pathTrace(); // TODO : pass a scene as parameter here : "pathTrace(scene);"
    static void draw();


    static Ray ray_generator(Camera const& cam,float const u,float const v);
    static bool compute_intersection(Ray const& r,Scene const& scene,IntersectData& intersection,int& index_intersected_primitive);
    static glm::vec3 getValue(Ray const& r,Scene const& scene);

};

}

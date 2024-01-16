#include "Renderer.h"

#include <string>
#include <cstdlib>

#include <glad/glad.h>

#include "Core/Application.h"
#include "GraphicCore.h"
#include "Screen.h"

#include "PathTracing/Ray.h"

#include "Scene/SceneObject.h"

#include "PathTracing/Pdf/CosinePdf.h"

namespace PathTracing
{

int N_sample_per_pixel = 2;
int max_depth = 5;

static Screen* s_screen;

void Renderer::init()
{
    s_screen = new Screen(Application::get()->getWindow()->getWidth(),
                          Application::get()->getWindow()->getHeight());
}

unsigned int Renderer::getViewportWidth() { return s_screen->getViewportWidth(); }
unsigned int Renderer::getViewportHeight() { return s_screen->getViewportHeight(); }

void Renderer::shutdown()
{
    delete s_screen;
}

void Renderer::begin(const glm::vec3& clearColor)
{
    s_screen->clear(clearColor);
}

void Renderer::pathTrace(std::shared_ptr<Image> image, std::shared_ptr<Scene> scene)
{
    for(unsigned int y = 0; y < image->getHeight(); y++)
    {
        float const v = static_cast<float>(y)/(image->getHeight()-1);
        for(unsigned int x = 0; x < image->getWidth(); x++)
        {
            float const u = static_cast<float>(x)/(image->getWidth()-1);

//            IntersectData intersection; //current intersection
//            int intersected_primitive = 0;  //current index of intersected primitive

            glm::vec3 color_average{0.0,0.0,0.0};

            for (int i =0 ;i <N_sample_per_pixel;i++ )
            {
                Ray ray = ray_generator(scene->getCamera(), u, v);

                glm::vec3 color = getValue(ray, *scene);

                color_average = color_average + color;
            }

            color_average = static_cast<float>((1.0/N_sample_per_pixel))*color_average;


//             glm::vec3 color = glm::vec3(std::fabs(ray.u().x));

//            bool is_intersected = compute_intersection(ray,empty_cornel_box,intersection,intersected_primitive);

            image->setData(x, y, color_average);
        }
    }
}

void Renderer::draw(const std::shared_ptr<Image>& image)
{
    s_screen->draw(image);
}

void Renderer::resize(unsigned int width, unsigned int height)
{
    s_screen->resize(width, height);
}

Ray Renderer::ray_generator(Camera const& cam,float const u,float const v)
{
    // position of the sample on the screen in 3D
    glm::vec3 const p_screen = screen_position(cam,u,v);

    // vector "camera center" to "screen position"
    glm::vec3 const d = p_screen-cam.center();

    // compute the ray
    Ray const r(cam.center(),d);

    return r;
}

bool Renderer::compute_intersection(Ray const& r, Scene const& scene, IntersectData& intersection, int& index_intersected_primitive)
{
    const unsigned int N_primitive = scene.getPrimitiveCount();

    bool found_intersection = false;
    unsigned int k = 0;
    float t = std::numeric_limits<float>::max();
    while(k < N_primitive)
    {
        const Primitive* primitive = scene.getPrimitive(k);
        bool is_intersection = primitive->intersect(r,intersection);
        if(is_intersection)
        {
            found_intersection = true;
            float new_relative = intersection.relative;
            if (new_relative <= t) {
                index_intersected_primitive = k;
                t = new_relative;
            }
        }

        ++k;
    }
    //Pour remettre la valeur de primitive correctement
    if (found_intersection)
    {
        const SceneObject* obj = scene.getSceneObject(index_intersected_primitive);

        const Primitive* primitive = scene.getPrimitive(index_intersected_primitive);
        primitive->intersect(r,intersection);
        glm::vec3 n = intersection.normal;
        CosinePdf* pdf = new CosinePdf(n);
        intersection.setPdf(pdf);
        intersection.setMaterial(obj->material);
    }

    return found_intersection;
}


glm::vec3 Renderer::getValue(Ray const& r, const Scene& scene)
{
    IntersectData intersection; //current intersection
    int intersected_primitive = 0;  //current index of intersected primitive

    bool is_intersected = compute_intersection(r, scene, intersection,intersected_primitive);

    if(is_intersected)
    {
        if (intersection.material->CanEmit())
        {
            return intersection.material->emitted();
        }
        else if (r.depth()+1 < max_depth)
        {
            Ray new_r = intersection.create_ray(r.depth());
            glm::vec3 L_in = getValue(new_r,scene);
            glm::vec3 value = intersection.getValue(r,new_r);
            return value*L_in;
        }
        else
        {
            return glm::vec3(0,0,0);
        }
        //return intersection.material->getAlbedo();
    }
    return glm::vec3(0,0,0);
}

}

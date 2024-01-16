#include "Renderer.h"

#include <string>
#include <cstdlib>

#include <glad/glad.h>

#include "Core/Application.h"
#include "GraphicCore.h"
#include "Screen.h"


//Include for Ugo test
#include "PathTracing/Ray.h"
#include "PathTracing/Camera.h"

#include "PathTracing/Scene/Scene.h"
#include "PathTracing/Scene/SceneObject.h"

#include "PathTracing/Primitives/Rectangle.h"
#include "PathTracing/Primitives/Sphere.h"
#include "PathTracing/Primitives/Plane.h"

#include "PathTracing/Materials/Lambertian.h"

#include "PathTracing/Pdf/CosinePdf.h"



namespace PathTracing
{

Scene empty_cornel_box;
Camera cam;
std::vector<SceneObject*> list_object;
int N_sample_per_pixel = 1;
int max_depth = 1;

static Screen* s_screen;

void Renderer::init()
{
    s_screen = new Screen(Application::get()->getWindow()->getWidth(),
                          Application::get()->getWindow()->getHeight());

    glm::vec3 red = glm::vec3(.65,.05,.05);
    glm::vec3 green = glm::vec3(.12,.45,.15);
    glm::vec3 light = glm::vec3(1,1,1);
    glm::vec3 white = glm::vec3(.73,.73,.73);
    glm::vec3 blue = glm::vec3(.05,.05,.65);

    empty_cornel_box = Scene();
    cam = empty_cornel_box.getCamera();
    cam.resize(getViewportWidth(), getViewportHeight());

    Rectangle* r1 = new Rectangle(glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(0,2,0),glm::vec3(0,0,1));
    Lambertian* l1 = new Lambertian(green);
    SceneObject* so1 = new SceneObject(r1,l1);
    empty_cornel_box.push_back(so1);

    Rectangle* r2 = new Rectangle(glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(0,2.00f,0),glm::vec3(0,0,1.00f));
    Lambertian* l2 = new Lambertian(red);
    SceneObject* so2 = new SceneObject(r2,l2);
    empty_cornel_box.push_back(so2);

    Rectangle* r3 = new Rectangle(glm::vec3(0.2,0.99,0.3),glm::vec3(-0.4,0,0),glm::vec3(0,0,0.4));
    Lambertian* l3 = new Lambertian(light);
    SceneObject* so3 = new SceneObject(r3,l3);
    empty_cornel_box.push_back(so3);

    Rectangle* r4 = new Rectangle(glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(-2.00f,0,0),glm::vec3(0,0,1.00f));
    Lambertian* l4 = new Lambertian(white);
    SceneObject* so4 = new SceneObject(r4,l4);
    empty_cornel_box.push_back(so4);

    Rectangle* r5 = new Rectangle(glm::vec3(1.00f,1.00f,0.00f),glm::vec3(-2.00f,0,0),glm::vec3(0,0.00f,1.0f));
    Lambertian* l5 = new Lambertian(white);
    SceneObject* so5 = new SceneObject(r5,l5);
    empty_cornel_box.push_back(so5);

    Rectangle* r6 = new Rectangle(glm::vec3(1,-1,1),glm::vec3(-2,0,0),glm::vec3(0,2,0));
    Lambertian* l6 = new Lambertian(blue);
    SceneObject* so6 = new SceneObject(r6,l6);
    empty_cornel_box.push_back(so6);

    Sphere* sphere = new Sphere(glm::vec3(-25.0f,20.0f,50.0f),3);//1.9999
    Lambertian* l7 = new Lambertian(red);
    SceneObject* so7 = new SceneObject(sphere,l7);
    //empty_cornel_box.push_back(so7);


    //Plane* plane = new Plane(glm::vec3(0.0f,0.0f,0.0f) , glm::vec3(0.0f,-1.0f,0.0f));//1.9999
    //Lambertian* l8 = new Lambertian(white);
    //SceneObject* so8 = new SceneObject(sphere,l7);
//    empty_cornel_box.push_back(so8);

    list_object = empty_cornel_box.getListObject();
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

void Renderer::pathTrace(std::shared_ptr<Image> image)
{
    for(unsigned int y = 0; y < image->getHeight(); y++)
    {
        float const v = static_cast<float>(y)/(image->getHeight()-1);
        for(unsigned int x = 0; x < image->getWidth(); x++)
        {
            float const u = static_cast<float>(x)/(image->getWidth()-1);

            //IntersectData intersection; //current intersection
            //int intersected_primitive = 0;  //current index of intersected primitive

            Ray ray = ray_generator(cam,u,v);

            glm::vec3 color = getValue(ray,empty_cornel_box);

//             glm::vec3 color = glm::vec3(std::fabs(ray.u().x));

            //bool is_intersected = compute_intersection(ray,empty_cornel_box,intersection,intersected_primitive);

            image->setData(x, y, color);
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
    cam.resize(width, height);
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
    int const N_primitive = scene.size_primitive();

    bool found_intersection = false;
    int k = 0;
    float t = std::numeric_limits<float>::max();
    while(k<N_primitive)
    {
        Primitive const & primitive = scene.get_primitive(k);
        bool is_intersection = primitive.intersect(r,intersection);
        if(is_intersection) {
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
        SceneObject* obj = scene.getSceneObject(index_intersected_primitive);

        Primitive const & primitive = scene.get_primitive(index_intersected_primitive);
        primitive.intersect(r,intersection);
        glm::vec3 n = intersection.normal;
        CosinePdf* pdf = new CosinePdf(n);
        intersection.setPdf(pdf);
        intersection.setMaterial(obj->material);
    }

    return found_intersection;
}


glm::vec3 Renderer::getValue(Ray const& r,Scene const& scene)
{
    IntersectData intersection; //current intersection
    int intersected_primitive = 0;  //current index of intersected primitive

    bool is_intersected = compute_intersection(r,empty_cornel_box,intersection,intersected_primitive);

    if (is_intersected)
    {
        /*if (intersection.material->CanEmit())
        {
            return intersection.material->emitted();
        }
        else if (r.depth() < N_sample_per_pixel)
        {
            Ray new_r = intersection.create_ray(r.depth());
            return intersection.getValue(r,new_r);
        }
        else
        {
            return glm::vec3(0,0,0);
        }*/
        return intersection.material->get_albedo();
    }

    return glm::vec3(0,0,0);
}

}

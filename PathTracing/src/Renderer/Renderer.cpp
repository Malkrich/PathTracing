#include "Renderer.h"

#include <string>
#include <cstdlib>

#include <glad/glad.h>

#include "Core/Application.h"
#include "GraphicCore.h"
#include "Image.h"
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




struct RenderData
{
    std::shared_ptr<Image> image;
    std::unique_ptr<Screen> screen;
};

static RenderData* s_renderData = nullptr;

void Renderer::init()
{
    s_renderData = new RenderData();

    s_renderData->image.reset(new Image(Application::get()->getWindow()->getWidth(),
                                        Application::get()->getWindow()->getHeight()));
    s_renderData->screen.reset(new Screen());

    glm::vec3 red = glm::vec3(.65,.05,.05);
    glm::vec3 green = glm::vec3(.12,.45,.15);
    glm::vec3 light = glm::vec3(1,1,1);
    glm::vec3 white = glm::vec3(.73,.73,.73);

    empty_cornel_box = Scene();
    cam = empty_cornel_box.getCamera();

    Rectangle* r1 = new Rectangle(glm::vec3(555.0f,0.0f,0.0f),glm::vec3(0,555,0),glm::vec3(0,0,555));
    Lambertian* l1 = new Lambertian(green);
    SceneObject* so1 = new SceneObject(r1,l1);
    //empty_cornel_box.push_back(so1);

    Rectangle* r2 = new Rectangle(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0,555,0),glm::vec3(0,0,555));
    Lambertian* l2 = new Lambertian(red);
    SceneObject* so2 = new SceneObject(r1,l1);
    //empty_cornel_box.push_back(so2);

    Rectangle* r3 = new Rectangle(glm::vec3(343,554,332),glm::vec3(-130,0,0),glm::vec3(0,0,105));
    Lambertian* l3 = new Lambertian(light);
    SceneObject* so3 = new SceneObject(r1,l1);
    //empty_cornel_box.push_back(so3);

    Rectangle* r4 = new Rectangle(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(555,0,0),glm::vec3(0,0,555));
    Lambertian* l4 = new Lambertian(white);
    SceneObject* so4 = new SceneObject(r1,l1);
    //empty_cornel_box.push_back(so4);

    Rectangle* r5 = new Rectangle(glm::vec3(555,555,555),glm::vec3(-555,0,0),glm::vec3(0,555,0));
    Lambertian* l5 = new Lambertian(white);
    SceneObject* so5 = new SceneObject(r1,l1);
    //empty_cornel_box.push_back(so5);

    Rectangle* r6 = new Rectangle(glm::vec3(0,0,555),glm::vec3(555,0,0),glm::vec3(0,555,0));
    Lambertian* l6 = new Lambertian(white);
    SceneObject* so6 = new SceneObject(r1,l1);
    //empty_cornel_box.push_back(so6);

    float aaa =  2.0f;
    Sphere* sphere = new Sphere(glm::vec3(1.0f,1.0,aaa),1);//1.9999
    Lambertian* l7 = new Lambertian(red);
    SceneObject* so7 = new SceneObject(sphere,l7);
    empty_cornel_box.push_back(so7);


    Plane* plane = new Plane(glm::vec3(0.0f,1.0f,0.0f) , glm::vec3(0.0f,-1.0f,0.0f));//1.9999
    Lambertian* l8 = new Lambertian(white);
    SceneObject* so8 = new SceneObject(sphere,l7);
    empty_cornel_box.push_back(so8);

    list_object = empty_cornel_box.getListObject();

}

void Renderer::shutdown()
{
    delete s_renderData;
}

void Renderer::begin(const glm::vec3& clearColor)
{
    s_renderData->screen->clear(clearColor);
}

void Renderer::pathTrace()
{
    std::shared_ptr<Image> image = s_renderData->image;

    for(unsigned int x = 0; x < image->getWidth(); x++)
    {
        float const u = static_cast<float>(x)/(image->getWidth()-1);
        for(unsigned int y = 0; y < image->getHeight(); y++)
        {
            float const v = static_cast<float>(y)/(image->getHeight()-1);
            //float r = (float)rand() / (float)RAND_MAX;
            //float g = (float)rand() / (float)RAND_MAX;
            //float b = (float)rand() / (float)RAND_MAX;

            //IntersectData intersection; //current intersection
            //int intersected_primitive = 0;  //current index of intersected primitive

            Ray ray = ray_generator(cam,u,v);

            glm::vec3 color = getValue(ray,empty_cornel_box);

            //bool is_intersected = compute_intersection(ray,empty_cornel_box,intersection,intersected_primitive);



            float r = color.x;
            float g = color.y;
            float b = color.z;

            (*image)(x, y) = {r, g, b};
        }
    }
}

void Renderer::draw()
{
    s_renderData->screen->draw(s_renderData->image);
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

    return glm::vec3(0,1,0);
}

}

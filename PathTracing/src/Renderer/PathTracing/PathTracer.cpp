#include "PathTracer.h"

#include "Renderer/PathTracing/Pdf/CosinePdf.h"
#include "Renderer/PathTracing/Pdf/HittablePdf.h"
#include "Renderer/PathTracing/Pdf/MixturePdf.h"


namespace PathTracing
{
static unsigned int s_accumalationCount = 0;

static glm::vec3 threshold1(glm::vec3 v)
{
        return glm::vec3(std::min(v.x, 1.0f),std::min(v.y, 1.0f),std::min(v.z, 1.0f));
}

void PathTracer::pathTrace(std::shared_ptr<Image> image, std::shared_ptr<Scene> scene)
{
    for(unsigned int y = 0; y < image->getHeight(); y++)
    {
        float const v = static_cast<float>(y)/(image->getHeight()-1);
        for(unsigned int x = 0; x < image->getWidth(); x++)
        {
            float const u = static_cast<float>(x)/(image->getWidth()-1);

            glm::vec3 current_color{0.0,0.0,0.0};

            for (unsigned int i = 0; i < scene->getRenderSettings().samplePerPixel; i++ )
            {
                Ray ray = ray_generator(scene->getCamera(), u, v);

                glm::vec3 color = threshold1(getValue(ray, *scene));

                current_color = current_color + color;

            }

            //current_color = static_cast<float>((1.0f / scene->getRenderSettings().samplePerPixel)) * current_color;

            float N = s_accumalationCount * scene->getRenderSettings().samplePerPixel;

            glm::vec3 color_average = (N*image->getPixel(x,y)+current_color)/(N+scene->getRenderSettings().samplePerPixel);

            image->setData(x, y, color_average);
        }
    }
    s_accumalationCount++;
}

void PathTracer::resetAccumultationCount()
{
    s_accumalationCount = 0;
}

Ray PathTracer::ray_generator(const Camera& cam, float u, float v)
{
    // position of the sample on the screen in 3D
    const glm::vec3 d = screen_position(cam, u, v) - cam.center();

    // compute the ray
    Ray r(cam.center(), d);

    return r;
}

bool PathTracer::compute_intersection(Ray const& r, Scene const& scene, IntersectData& intersection, int& index_intersected_primitive)
{
    const unsigned int N_primitive = scene.getPrimitiveCount();

    bool found_intersection = false;
    unsigned int k = 0;
    float t = std::numeric_limits<float>::max();
    while(k < N_primitive)
    {
        const std::shared_ptr<Primitive>& primitive = scene.getPrimitive(k);
        bool is_intersection = primitive->intersect(r, intersection);
        if(is_intersection)
        {
            found_intersection = true;
            float new_relative = intersection.m_relative;
            if (new_relative <= t)
            {
                index_intersected_primitive = k;
                t = new_relative;
            }
        }
        ++k;
    }
    //Pour remettre la valeur de primitive correctement
    if(found_intersection)
    {
        std::shared_ptr<SceneObject> obj = scene.getSceneObject(index_intersected_primitive);

        std::shared_ptr<Primitive> primitive = scene.getPrimitive(index_intersected_primitive);
        primitive->intersect(r, intersection);
        glm::vec3 n = intersection.m_normal;


        std::vector<int> listIndexLight = scene.getListIndexLight();
        std::vector<std::shared_ptr<Pdf>> listPdf;

        std::shared_ptr<Pdf> pdfCosine = std::make_shared<CosinePdf>(n);
        listPdf.push_back(pdfCosine);

        std::vector<std::shared_ptr<SceneObject>> lights = scene.getLights();

//        for (int index : listIndexLight)
//        {
//            std::shared_ptr<SceneObject> light = scene.getSceneObject(index);
//            std::shared_ptr<Pdf> pdfLight = std::make_shared<HittablePdf>(*light,intersection.position,n);
//            listPdf.push_back(pdfLight);
//        }

        for (std::shared_ptr<SceneObject> light : lights)
        {
            std::shared_ptr<Pdf> pdfLight = std::make_shared<HittablePdf>(*light,intersection.m_position,n);
            listPdf.push_back(pdfLight);
        }

        std::shared_ptr<SceneObject> light = scene.getSceneObject(2);
        std::shared_ptr<Pdf> pdfLight = std::make_shared<HittablePdf>(*light,intersection.m_position,n);

//        std::shared_ptr<SceneObject> light2 = scene.getSceneObject(7);
//        std::shared_ptr<Pdf> pdfLight2 = std::make_shared<HittablePdf>(*light2,intersection.position,n);
//        std::shared_ptr<Pdf> pdf = std::make_shared<MixturePdf>(pdfLight,pdfLight2);


        //std::shared_ptr<Pdf> pdf = pdfCosine;
        //std::shared_ptr<Pdf> pdf = pdfLight;
        //std::shared_ptr<Pdf> pdf = std::make_shared<MixturePdf>(listPdf);
        //std::shared_ptr<Pdf> pdf = intersection.material->createPdf(lights,intersection.position,n);
        //std::cout<<"Coucou : "<<index_intersected_primitive<<std::endl;
        std::shared_ptr<Pdf> pdf = obj->material->createPdf(lights,intersection.m_position,n);
        //std::cout<<obj->material->test()<<std::endl;



        intersection.setPdf(pdf);
        intersection.setMaterial(obj->material);
    }

    return found_intersection;
}

glm::vec3 PathTracer::getValue(const Ray& r, const Scene& scene)
{
    IntersectData intersection; //current intersection
    int intersected_primitive = 0;  //current index of intersected primitive

    bool is_intersected = compute_intersection(r, scene, intersection, intersected_primitive);

    if(is_intersected)
    {
        if (intersection.m_material->CanEmit())
        {
            return intersection.m_material->emitted();
        }
        else if (r.getDepth() + 1 < scene.getRenderSettings().maxDepth)
        {
            Ray newR = intersection.create_ray(r, r.getDepth());
            int count = 0;
            while (dot(newR.getU(),intersection.m_normal) < 0 &&(count<10))
            {
                newR = intersection.create_ray(r, r.getDepth());
                count++;
            }
            if (dot(newR.getU(),intersection.m_normal) < 0)
            {
                return glm::vec3(0,0,0);
            }
            newR.addOffset();
            glm::vec3 L_in = getValue(newR, scene);
            //std::cout<<"L_in : "<<L_in.x<<"  "<<L_in.y<<"  "<<L_in.z<<std::endl;
            glm::vec3 value = intersection.getValue(r, newR);
            //if (intersected_primitive == 0) {
                //std::cout<<value.x<<"   "<<value.y<<"   "<<value.z<<std::endl;
                //return glm::vec3(0,0,0);
            //}

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

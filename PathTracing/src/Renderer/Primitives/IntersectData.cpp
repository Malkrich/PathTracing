#include "IntersectData.h"

namespace PathTracing
{

IntersectData::IntersectData()
    :position(glm::vec3()),normal(glm::vec3(0,0,1)),relative(-1.0f)
{}

IntersectData::IntersectData(glm::vec3 const& position_param,
                      glm::vec3 const& normal_param,
                      float relative_param,
                      std::shared_ptr<Pdf> pdf_param,
                      std::shared_ptr<Material> material_param)
    : position(position_param)
    , normal(normal_param)
    , relative(relative_param)
    , pdf(pdf_param)
    , material(material_param)
{}

void IntersectData::set(glm::vec3 const& position_param,
         glm::vec3 const& normal_param,
         float relative_param)
{
    position = position_param;
    normal   = normal_param;
    relative = relative_param;
}

void IntersectData::setMaterial(std::shared_ptr<Material> material_param)
{
    material = material_param;
}

void IntersectData::setPdf(std::shared_ptr<Pdf> pdf_param)
{
    pdf = pdf_param;
}

Ray IntersectData::create_ray(Ray r_in,int depth)
{
    glm::vec3 p0 = position;
    //std::cout<<"position : "<<position.x<<"  "<<position.y<<"  "<<position.z<<std::endl;
    glm::vec3 u = pdf->generate(r_in);
    //std::cout<<"u : "<<u.x<<"  "<<u.y<<"  "<<u.z<<std::endl;
    Ray ray = Ray(p0,u,depth+1);
    return ray;
}

glm::vec3 IntersectData::getValue(Ray ray_out,Ray ray_in)
{
    //glm::vec3 res;
    glm::vec3 u_out = ray_out.u();
    glm::vec3 u_in = ray_in.u();

    float attenuation = glm::dot(normalize(u_in), normalize(normal));

    float p_value = pdf->value(u_in);

    //glm::vec3 L_in = ray_in.getValue();

    float lambda = 0.0f;
    float theta_out = acos(dot(normalize(normal), normalize(u_out)));
    float theta_in = acos(dot(normalize(normal), normalize(u_in)));
    float fr = material->brdf(position, theta_out, theta_in, lambda);

    const glm::vec3& color = material->getAlbedo(position, theta_out, theta_in, lambda);

    //res = color*attenuation*fr*L_in/p_value; //Originel
    //res = attenuation*fr*L_in/p_value; // Originel sans color
    glm::vec3 res = color*attenuation*fr/p_value;
    //glm::vec3 res = color*attenuation*fr;

    //std::cout<<"attenuation : "<<attenuation<<std::endl;
    //std::cout<<"fr : "<<fr<<std::endl;
    //std::cout<<"p_value : "<<p_value<<std::endl;
    //std::cout<<"Multiplication"<<p_value*res.x<<"  "<<p_value*res.y<<"  "<<p_value*res.z<<std::endl;
    //std::cout<<L_in.x<<"  "<<L_in.y<<"  "<<L_in.z<<std::endl;


    return res;
}


/*std::ostream& operator<<(std::ostream& stream,IntersectData const& intersection)
{
    stream<<intersection.position<<" "<<intersection.normal<<" "<<intersection.relative;
    return stream;
}*/

}

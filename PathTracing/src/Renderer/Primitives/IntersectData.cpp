#include "IntersectData.h"

namespace PathTracing
{

IntersectData::IntersectData()
    :position(glm::vec3()),normal(glm::vec3(0,0,1)),relative(-1.0f)
{}

IntersectData::IntersectData(glm::vec3 const& position_param,
                      glm::vec3 const& normal_param,
                      float relative_param,
                      Pdf* pdf_param,
                      Material* material_param)
    :position(position_param),normal(normal_param),relative(relative_param),pdf(pdf_param),material(material_param)
{}

void IntersectData::set(glm::vec3 const& position_param,
         glm::vec3 const& normal_param,
         float relative_param)
{
    position = position_param;
    normal   = normal_param;
    relative = relative_param;
}

void IntersectData::setMaterial(Material* material_param) {
    material = material_param;
}

void IntersectData::setPdf(Pdf *pdf_param)
{
    pdf = pdf_param;
}

Ray IntersectData::create_ray(int depth)
{
    glm::vec3 p0 = position;
    glm::vec3 u = pdf->generate();
    Ray ray = Ray(p0,u,depth+1);
    return ray;
}

glm::vec3 IntersectData::getValue(Ray ray_out,Ray ray_in)
{
    //glm::vec3 res;
    glm::vec3 u_out = ray_out.u();
    glm::vec3 u_in = ray_in.u();

    float attenuation = glm::dot(normalize(u_in),normalize(normal));

    float p_value = pdf->value(u_in);

    glm::vec3 L_in = ray_in.getValue();

    float lambda;
    float theta_out = acos(dot(normalize(normal),normalize(u_out)));
    float theta_in = acos(dot(normalize(normal),normalize(u_in)));
    float fr = material->brdf(position,theta_out,theta_in,lambda);

    const glm::vec3& color = material->getAlbedo(position,theta_out,theta_in,lambda);

    //res = color*attenuation*fr*L_in/p_value; //Originel
    //res = attenuation*fr*L_in/p_value; // Originel sans color
    glm::vec3 res = color*attenuation*fr/p_value;

    //std::cout<<fr*attenuation/p_value<<std::endl;
    //std::cout<<res.x<<"  "<<res.y<<"  "<<res.z<<std::endl;
    //std::cout<<L_in.x<<"  "<<L_in.y<<"  "<<L_in.z<<std::endl;


    return res;
}


/*std::ostream& operator<<(std::ostream& stream,IntersectData const& intersection)
{
    stream<<intersection.position<<" "<<intersection.normal<<" "<<intersection.relative;
    return stream;
}*/

}

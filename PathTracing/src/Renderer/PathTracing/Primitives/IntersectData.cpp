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

Ray IntersectData::create_ray()
{
    glm::vec3 p0 = position;
    glm::vec3 u = pdf->generate();
    Ray ray = Ray(p0,u);
    return ray;
}

glm::vec3 IntersectData::getValue(Ray* ray_out,Ray* ray_in)
{
    glm::vec3 res;
    glm::vec3 u_out = ray_out->u();
    glm::vec3 u_in = ray_in->u();

    float attenuation = glm::dot(normalize(u_in),normalize(normal));

    float p_value = pdf->value(u_in);

    glm::vec3 L_in = ray_in->getValue();

    float lambda;
    float theta_out = acos(dot(normalize(normal),normalize(u_out)));
    float theta_in = acos(dot(normalize(normal),normalize(u_in)));
    float fr = material->brdf(position,theta_out,theta_in,lambda);

    glm::vec3 color = material->get_albedo(position,theta_out,theta_in,lambda);

    res = color*attenuation*fr*L_in/p_value;

    return res;
}


/*std::ostream& operator<<(std::ostream& stream,IntersectData const& intersection)
{
    stream<<intersection.position<<" "<<intersection.normal<<" "<<intersection.relative;
    return stream;
}*/

}

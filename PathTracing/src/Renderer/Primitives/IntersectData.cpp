#include "IntersectData.h"

namespace PathTracing
{

IntersectData::IntersectData()
    : m_position(glm::vec3())
    , m_normal(glm::vec3(0,0,1))
    , m_relative(-1.0f)
{}

IntersectData::IntersectData(glm::vec3 const& position,
                      glm::vec3 const& normal,
                      float relative,
                      std::shared_ptr<Pdf> pdf,
                      std::shared_ptr<Material> material)
    : m_position(position)
    , m_normal(normal)
    , m_relative(relative)
    , m_pdf(pdf)
    , m_material(material)
{}

void IntersectData::set(glm::vec3 const& position,
         glm::vec3 const& normal,
         float relative)
{
    m_position = position;
    m_normal   = normal;
    m_relative = relative;
}

void IntersectData::setMaterial(std::shared_ptr<Material> material_param)
{
    m_material = material_param;
}

void IntersectData::setPdf(std::shared_ptr<Pdf> pdf_param)
{
    m_pdf = pdf_param;
}

Ray IntersectData::create_ray(Ray r_in,int depth)
{
    glm::vec3 p0 = m_position;
    //std::cout<<"position : "<<position.x<<"  "<<position.y<<"  "<<position.z<<std::endl;
    glm::vec3 u = m_pdf->generate(r_in);
    //std::cout<<"u : "<<u.x<<"  "<<u.y<<"  "<<u.z<<std::endl;
    Ray ray = Ray(p0,u,depth+1);
    return ray;
}

glm::vec3 IntersectData::getValue(const Ray& rayOut, const Ray& rayIn)
{
    //glm::vec3 res;
    glm::vec3 uOut = rayOut.getU();
    glm::vec3 uIn = rayIn.getU();

    float attenuation = glm::dot(normalize(uIn), normalize(m_normal));

    float p_value = m_pdf->value(uIn);

    //glm::vec3 L_in = ray_in.getValue();

    float lambda = 0.0f;
    float thetaOut = acos(dot(normalize(m_normal), normalize(uOut)));
    float thetaIn = acos(dot(normalize(m_normal), normalize(uIn)));
    float fr = m_material->brdf(m_position, thetaOut, thetaIn, lambda);

    const glm::vec3& color = m_material->getAlbedo(m_position, thetaOut, thetaIn, lambda);

    //res = color*attenuation*fr*L_in/p_value; //Originel
    //res = attenuation*fr*L_in/p_value; // Originel sans color
    glm::vec3 res = color * attenuation * fr / p_value;
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

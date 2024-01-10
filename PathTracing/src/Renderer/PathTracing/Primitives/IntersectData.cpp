#include "IntersectData.h"

namespace PathTracing
{

IntersectData::IntersectData()
    :position(glm::vec3()),normal(glm::vec3(0,0,1)),relative(-1.0f)
{}

IntersectData::IntersectData(glm::vec3 const& position_param,
                      glm::vec3 const& normal_param,
                      float relative_param,Pdf* pdf_param)
    :position(position_param),normal(normal_param),relative(relative_param),pdf(pdf_param)
{}

void IntersectData::set(glm::vec3 const& position_param,
         glm::vec3 const& normal_param,
         float relative_param)
{
    position = position_param;
    normal   = normal_param;
    relative = relative_param;
}


/*std::ostream& operator<<(std::ostream& stream,IntersectData const& intersection)
{
    stream<<intersection.position<<" "<<intersection.normal<<" "<<intersection.relative;
    return stream;
}*/

}

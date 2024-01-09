#include "Primitive.h"

#ifndef PLANE_H
#define PLANE_H

namespace PathTracing
{
class Plane : public Primitive
{

public:
    Plane(glm::vec3 const& position_param,glm::vec3 const& normal_param);

    /*Return Point of the plane*/
    glm::vec3 const& position() const;
    /*Return normal of the plane*/
    glm::vec3 const& normal() const;

private:
    glm::vec3 position_data;
    glm::vec3 normal_data;

};


}



#endif // PLANE_H

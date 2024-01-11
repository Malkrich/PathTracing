#include "Plane.h"

#include <cmath>

namespace PathTracing
{

Plane::Plane(glm::vec3 const& position_param,glm::vec3 const& normal_param)
    :position_data(position_param),normal_data(normal_param)
{

}

glm::vec3 const& Plane::position() const
{
    return position_data;
}
glm::vec3 const& Plane::normal() const
{
    return normal_data;
}


bool Plane::intersect(Ray const& ray_param,IntersectData& intersection) const
{
    //Le code suivant est arbitraire est doit etre modifie
    glm::vec3 xs = ray_param.p0();
    glm::vec3 const& u = ray_param.u();
    glm::vec3 const& np = normal_data;
    glm::vec3 xp = position_data;

    float const t=-1.0f *dot(xs-xp,np)/dot(u,np);

    if(t>0){
        //glm::vec3 x_inter = xs+t*u;
        //intersection.set(x_inter,np,t);
        return true;
    }
    else
        return false;


}

}

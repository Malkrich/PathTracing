#include "Rectangle.h"

#include <cmath>

namespace PathTracing
{

Rectangle::Rectangle(glm::vec3 const& p_param,glm::vec3 const& v1_param,glm::vec3 const& v2_param)
    :p_data(p_param),v1_data(v1_param),v2_data(v2_param)
{
    normal_data = glm::normalize(glm::cross(v1_param,v2_param));
}

glm::vec3 const& Rectangle::p() const
{
    return p_data;
}

glm::vec3 const& Rectangle::v1() const
{
    return v1_data;
}

glm::vec3 const& Rectangle::v2() const
{
    return v2_data;
}


glm::vec3 const& Rectangle::normal() const
{
    return normal_data;
}


bool Rectangle::intersect(Ray const& ray_param,IntersectData& intersection) const
{

    //Le code suivant est arbitraire est doit etre modifie
    glm::vec3 xs = ray_param.p0();
    glm::vec3 const& u = ray_param.u();
    glm::vec3 const& np = normal_data;
    glm::vec3 xp = p_data;

    float const t=-1.0f *dot(xs-xp,np)/dot(u,np);



    if(t>0){
        glm::vec3 x_inter = xs+t*u;

        glm::vec3 w = np / dot(np,np);
        glm::vec3 p = x_inter-xp;
        float alpha = dot(w,cross(p,v2_data)) ;
        float beta = dot(w,cross(v1_data,p));

        if (0<alpha && alpha<1 && 0<beta && beta<1)
        {
            intersection.set(x_inter,np,t);
            return true;
        }

    }

    return false;


}

}

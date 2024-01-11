/*
**    TP CPE Lyon
**    Copyright (C) 2015 Damien Rohmer
**
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Sphere.h"


#include <cmath>

namespace PathTracing
{

Sphere::Sphere(glm::vec3 const& center_param,float radius_param)
    :center_data(center_param),radius_data(radius_param)
{}

glm::vec3 const& Sphere::center() const
{
    return center_data;
}
float Sphere::radius() const
{
    return radius_data;
}

bool Sphere::intersect(Ray const& ray_param,IntersectData& intersection) const
{


    glm::vec3 const& u = ray_param.u();
    glm::vec3 const& x0 = center_data;
    float const& r = radius_data;
    glm::vec3 const& xs = ray_param.p0();

    float a = pow(glm::length(u),2);
    float b = 2*dot(xs-x0,u);
    float c = pow(glm::length(xs-x0),2)-pow(r,2);

    float Delta = pow(b,2)-4*a*c;

    if(Delta>0.0f)
    {
        float t1 = (-b-sqrt(Delta))/2*a;
        float t2 = (-b+sqrt(Delta))/2*a;

        if (t1 >= 0.0f) {
            /*
            glm::vec3 x_inter = xs+t1*u;
            glm::vec3 n = glm::normalize(x_inter -x0);
            intersection.set(x_inter,n,t1);*/
            return true;
        }
        else if (t2 >= 0.0f) {
            /*
            glm::vec3 x_inter = xs+t2*u;
            glm::vec3 n = glm::normalize(x_inter -x0);
            intersection.set(x_inter,n,t2);*/
            return true;
        }
        else {
            return false;
        }

    }
    else if (Delta == 0.0f){
        float t = -b/2*a;
        if (t >= 0.0f) {
            /*
            glm::vec3 x_inter = xs+t*u;
            glm::vec3 n = glm::normalize(x_inter -x0);
            intersection.set(x_inter,n,t);*/
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }


}



}

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

Sphere::Sphere(const glm::vec3& center, float radius)
    : m_center(center)
    , m_radius(radius)
{}

bool Sphere::intersect(Ray const& ray_param, IntersectData& intersection) const
{
    const glm::vec3& u  = ray_param.u();
    const glm::vec3& x0 = m_center;
    const float r       = m_radius;
    const glm::vec3& xs = ray_param.p0();

    float a = pow(glm::length(u), 2);
    float b = 2*dot(xs - x0, u);
    float c = pow(glm::length(xs-x0), 2) - pow(r, 2);

    float delta = pow(b, 2) - 4*a*c;

    if(delta > 0.0f)
    {
        float t1 = (-b - sqrt(delta)) / 2*a;
        float t2 = (-b + sqrt(delta)) / 2*a;

        if (t1 >= 0.0f)
        {
            glm::vec3 x_inter = xs + t1 * u;
            glm::vec3 n = glm::normalize(x_inter - x0);
            intersection.set(x_inter, n, t1);
            return true;
        }
        else if (t2 >= 0.0f)
        {
            glm::vec3 x_inter = xs + t2 * u;
            glm::vec3 n = glm::normalize(x_inter -x0);
            intersection.set(x_inter, n, t2);
            return true;
        }
        else
            return false;
    }
    else if (delta == 0.0f)
    {
        float t = -b / 2*a;
        if (t >= 0.0f)
        {
            glm::vec3 x_inter = xs + t * u;
            glm::vec3 n = glm::normalize(x_inter - x0);
            intersection.set(x_inter, n, t);
            return true;
        }
        else
            return false;
    }
    else
        return false;

//    float a = square( norm(u) );
//     float b = 2 * dot(x_0 - x_s, u);
//     float c = square( norm(x_0 - x_s) ) - square(radius_data);
//     // calcul de delta
//     float delta = square(b) - 4 * a * c;

//     float t_inter = 0.0f;
//     if(delta > 0.0f)
//     {
//         // 2 solutions
//          (-b +/- sqrt(delta)) / (2 * a)
//         float t_min = ( -b - sqrt(delta) ) / ( 2.0f * a ); // plus petite solutiojn
//         float t_max = ( -b + sqrt(delta) ) / ( 2.0f * a ); // plus grande solution
//         t_inter = t_min > 0.0f ? t_min : t_max; // on garde la solution t_min si t_min est positif, sinon on prend t_max
//     }
//     else if(delta == 0.0f)
//     {
//         // 1 solution
//         // -b / 2 * a
//         t_inter = -b / (2.0f * a);
//     }
//     else if(delta < 0.0f)
//     {
//         // aucune solution
//         t_inter = -1.0f;
//     }

//     vec3 p_inter    = x_0 + t_inter * u;
//     vec3 n          = normalized(p_inter - center_data);
//     intersection.set(p_inter, n, t_inter);

//     return t_inter > 0.0f;
}



}

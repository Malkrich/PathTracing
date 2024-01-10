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

#include "Ray.h"
#include <cmath>

namespace PathTracing
{

Ray::Ray()
    :p0_data(glm::vec3()),u_data(glm::vec3(1.0f,0.0f,0.0f))
{}

Ray::Ray(glm::vec3 const& p0_param,glm::vec3 const& u_param)
    :p0_data(p0_param),u_data(glm::normalize(u_param))
{}

glm::vec3 const& Ray::p0() const {return p0_data;}
glm::vec3 const& Ray::u() const {return u_data;}


glm::vec3 Ray::operator()(float const t) const
{
    return p0_data + t*u_data;
}

void Ray::offset(float const epsilon)
{
    p0_data += epsilon*u_data;
}

glm::vec3 Ray::getValue() {
    return glm::vec3(1.0f,1.0f,1.0f);
}

/*
std::ostream& operator<<(std::ostream& stream,Ray const& r)
{
    stream<<r.p0()<<" , "<<r.u();
    return stream;
}*/


}

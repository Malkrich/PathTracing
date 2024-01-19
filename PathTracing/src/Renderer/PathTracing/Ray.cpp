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
    : Ray(glm::vec3(), glm::vec3(1.0f,0.0f,0.0f), 0)
{}

Ray::Ray(const glm::vec3& p0, const glm::vec3& u)
    : Ray(p0, u, 0)
{}

Ray::Ray(const glm::vec3& p0, const glm::vec3& u, int depth)
    : m_p0(p0)
    , m_u(glm::normalize(u))
    , m_depth(depth)
{}

glm::vec3 Ray::operator()(float t) const
{
    return m_p0 + t*m_u;
}

void Ray::offset(float epsilon)
{
    m_p0 += epsilon * m_u;
}

glm::vec3 Ray::getValue()
{
    return glm::vec3(1.0f, 1.0f, 1.0f);
}

/*
std::ostream& operator<<(std::ostream& stream,Ray const& r)
{
    stream<<r.p0()<<" , "<<r.u();
    return stream;
}*/


}

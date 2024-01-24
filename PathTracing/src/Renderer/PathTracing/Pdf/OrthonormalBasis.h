#ifndef ORTHONORMALBASIS_H
#define ORTHONORMALBASIS_H

#include <glm/glm.hpp>

namespace PathTracing {

class OrthonormalBasis
{
public:
    OrthonormalBasis() = default;

    const glm::vec3& operator[](int i) const { return axis[i]; }
    glm::vec3& operator[](int i) { return axis[i]; }

    const glm::vec3& getU() const { return axis[0]; }
    const glm::vec3& getV() const { return axis[1]; }
    const glm::vec3& getW() const { return axis[2]; }

    glm::vec3 local(float a, float b, float c) const
    {
        return a*getU() + b*getV() + c*getW();
    }

    glm::vec3 local(const glm::vec3& a) const
    {
        return local(a.x, a.y, a.z);
    }

    void buildFromW(const glm::vec3& w)
    {
        glm::vec3 unit_w = glm::normalize(w);
        glm::vec3 a = (fabs(unit_w.x) > 0.9) ? glm::vec3(0,1,0) : glm::vec3(1,0,0);
        glm::vec3 v = glm::normalize(cross(unit_w, a));
        glm::vec3 u = cross(unit_w, v);
        axis[0] = u;
        axis[1] = v;
        axis[2] = unit_w;
    }

public:
    glm::vec3 axis[3];
};

}

#endif // ORTHONORMALBASIS_H

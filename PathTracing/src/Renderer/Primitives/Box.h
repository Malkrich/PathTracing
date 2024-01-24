#ifndef BOX_H
#define BOX_H

#include <vector>

#include "Primitive.h"
#include "Rectangle.h"

namespace PathTracing
{
class Box : public Primitive
{
public:
    Box(const glm::vec3& p1_param, const glm::vec3& p2_param);

    virtual bool intersect(Ray const& ray_param,IntersectData& intersection) const override;
    virtual glm::vec3& getPosition() override { return m_p1; }
    virtual const glm::vec3& getPosition() const override { return m_p1; }
    virtual void rotate(const glm::quat&) override {}

private:
    glm::vec3 m_p1;
    glm::vec3 m_p2;
    Rectangle* m_bottom;
    Rectangle* m_top;
    Rectangle* m_f1;
    Rectangle* m_f2;
    Rectangle* m_f3;
    Rectangle* m_f4;
    Rectangle* m_listRectangle[6];
};
}

#endif // BOX_H

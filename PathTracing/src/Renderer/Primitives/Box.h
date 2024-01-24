#ifndef BOX_H
#define BOX_H

#include <vector>
#include <memory>

#include "Primitive.h"
#include "Rectangle.h"

namespace PathTracing
{

class Box : public Primitive
{
public:
    Box(const glm::vec3& p1, const glm::vec3& p2);

    virtual bool intersect(Ray const& ray, IntersectData& intersection) const override;
    virtual glm::vec3& getPosition() override { return m_p1; }
    virtual const glm::vec3& getPosition() const override { return m_p1; }
    virtual void rotate(const glm::quat&) override {}

private:
    glm::vec3 m_p1;
    glm::vec3 m_p2;
    std::vector<std::shared_ptr<Rectangle>> m_listRectangle;
};

}

#endif // BOX_H

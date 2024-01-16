#include "Primitive.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H


namespace PathTracing
{
class Rectangle : public Primitive
{
public:
    Rectangle(const glm::vec3& p_param, const glm::vec3& v1_param, const glm::vec3& v2_param);

    /*Return the point of the Rectangle*/
    const glm::vec3& p() const { return m_p; }

    /*Return the two vectors*/
    const glm::vec3& v1() const { return m_v1; }
    const glm::vec3& v2() const { return m_v2; }

    /*Return normal of the Rectangle*/
    const glm::vec3& normal() const { return m_normal; }

    virtual bool intersect(Ray const& ray_param,IntersectData& intersection) const override;
    virtual glm::vec3& getPosition() override { return m_p; }
    virtual const glm::vec3& getPosition() const override { return m_p; }
    virtual void rotate(const glm::quat& rotation) override;

private:
    glm::vec3 m_p;
    glm::vec3 m_v1;
    glm::vec3 m_v2;
    glm::vec3 m_normal;

};

}


#endif // RECTANGLE_H

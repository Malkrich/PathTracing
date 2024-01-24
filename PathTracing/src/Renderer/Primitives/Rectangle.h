#include "Primitive.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H


namespace PathTracing
{
class Rectangle : public Primitive
{
public:
    Rectangle(const glm::vec3& p, const glm::vec3& v1, const glm::vec3& v2);

    /*Return the point of the Rectangle*/
    const glm::vec3& p() const { return m_p; }

    /*Return the two vectors*/
    const glm::vec3& v1() const { return m_v1; }
    const glm::vec3& v2() const { return m_v2; }

    /*Return normal of the Rectangle*/
    const glm::vec3& normal() const { return m_normal; }

    virtual bool intersect(Ray const& ray_param, IntersectData& intersection) const override;
    virtual glm::vec3& getPosition() override { return m_p; }
    virtual const glm::vec3& getPosition() const override { return m_p; }
    virtual void rotate(const glm::quat&) override {}

    double pdf_value(const glm::vec3& o, const glm::vec3& n, const glm::vec3& v) const override;
    glm::vec3 random(const glm::vec3& o) const override;

private:
    glm::vec3 m_p;
    glm::vec3 m_v1;
    glm::vec3 m_v2;
    glm::vec3 m_normal;
    double m_area;
};

}


#endif // RECTANGLE_H

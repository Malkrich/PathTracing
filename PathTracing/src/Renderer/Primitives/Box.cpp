#include <iostream>

#include "Box.h"
#include "Rectangle.h"

namespace PathTracing
{
Box::Box(const glm::vec3& p1_param,const glm::vec3& p2_param):m_p1(p1_param),m_p2(p2_param)
{
    float x1 = std::min(p1_param.x,p2_param.x);
    float y1 = std::min(p1_param.y,p2_param.y);
    float z1 = std::min(p1_param.z,p2_param.z);
    float x2 = std::max(p1_param.x,p2_param.x);
    float y2 = std::max(p1_param.y,p2_param.y);
    float z2 = std::max(p1_param.z,p2_param.z);
    glm::vec3 p1 = p1_param;
    glm::vec3 p2 = glm::vec3(x2,y1,z1);
    glm::vec3 p3 = glm::vec3(x1,y1,z2);
    glm::vec3 p4 = glm::vec3(x2,y1,z2);
    glm::vec3 p5 = glm::vec3(x1,y2,z1);
    glm::vec3 p6 = glm::vec3(x2,y2,z1);
    glm::vec3 p7 = glm::vec3(x1,y2,z2);
    glm::vec3 p8 = p2_param;
    m_bottom = new Rectangle(p1,p2-p1,p3-p1);
    m_f1 = new Rectangle(p1,p2-p1,p5-p1);
    m_f2 = new Rectangle(p2,p4-p2,p6-p2);
    m_f3 = new Rectangle(p4,p3-p4,p8-p4);
    m_f4 = new Rectangle(p3,p1-p3,p7-p3);
    m_top = new Rectangle(p5,p6-p5,p7-p5);
    m_listRectangle[0] = m_bottom;
    m_listRectangle[1] = m_f1;
    m_listRectangle[2] = m_f2;
    m_listRectangle[3] = m_f3;
    m_listRectangle[4] = m_f4;
    m_listRectangle[5] = m_top;
}

bool Box::intersect(Ray const& ray,IntersectData& intersection) const
{
    bool found_intersection = false;
    int index_intersected_primitive = 0;
    unsigned int k = 0;
    float t = std::numeric_limits<float>::max();
    while(k < 6)
    {
        const Rectangle* rectangle = m_listRectangle[k];//std::shared_ptr<Rectangle>&
        bool is_intersection = rectangle->intersect(ray, intersection);
        if(is_intersection)
        {
            found_intersection = true;
            float new_relative = intersection.relative;
            if (new_relative <= t) {
                index_intersected_primitive = k;
                t = new_relative;
            }
        }
        ++k;
    }
    if(found_intersection)
    {
        Rectangle* rectangle = m_listRectangle[index_intersected_primitive]; //std::shared_ptr<Primitive>
        rectangle->intersect(ray, intersection);
    }
    return found_intersection;
}

}

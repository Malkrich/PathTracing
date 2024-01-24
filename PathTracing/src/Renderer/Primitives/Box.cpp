#include <iostream>

#include "Box.h"
#include "Rectangle.h"

#define NUM_FACES 6

namespace PathTracing
{
Box::Box(const glm::vec3& p1, const glm::vec3& p2)
    : m_p1(p1)
    , m_p2(p2)
    , m_listRectangle(NUM_FACES)
{
    float x1 = glm::min(p1.x, p2.x);
    float y1 = glm::min(p1.y, p2.y);
    float z1 = glm::min(p1.z, p2.z);
    float x2 = glm::max(p1.x, p2.x);
    float y2 = glm::max(p1.y, p2.y);
    float z2 = glm::max(p1.z, p2.z);
    glm::vec3 p1Rect = p1;
    glm::vec3 p2Rect = glm::vec3(x2, y1, z1);
    glm::vec3 p3Rect = glm::vec3(x1, y1, z2);
    glm::vec3 p4Rect = glm::vec3(x2, y1, z2);
    glm::vec3 p5Rect = glm::vec3(x1, y2, z1);
    glm::vec3 p6Rect = glm::vec3(x2, y2, z1);
    glm::vec3 p7Rect = glm::vec3(x1, y2, z2);
    glm::vec3 p8Rect = p2;
    m_listRectangle[0] = std::make_shared<Rectangle>(p1Rect, p2Rect-p1Rect, p3Rect-p1Rect);
    m_listRectangle[1] = std::make_shared<Rectangle>(p1Rect, p2Rect-p1Rect, p5Rect-p1Rect);
    m_listRectangle[2] = std::make_shared<Rectangle>(p2Rect, p4Rect-p2Rect, p6Rect-p2Rect);
    m_listRectangle[3] = std::make_shared<Rectangle>(p4Rect, p3Rect-p4Rect, p8Rect-p4Rect);
    m_listRectangle[4] = std::make_shared<Rectangle>(p3Rect, p1Rect-p3Rect, p7Rect-p3Rect);
    m_listRectangle[5] = std::make_shared<Rectangle>(p5Rect, p6Rect-p5Rect, p7Rect-p5Rect);
}

bool Box::intersect(Ray const& ray, IntersectData& intersection) const
{
    bool found_intersection = false;
    int index_intersected_primitive = 0;
    unsigned int k = 0;
    float t = std::numeric_limits<float>::max();
    while(k < NUM_FACES)
    {
        const std::shared_ptr<Rectangle>& rectangle = m_listRectangle[k];
        bool is_intersection = rectangle->intersect(ray, intersection);
        if(is_intersection)
        {
            found_intersection = true;
            float new_relative = intersection.m_relative;
            if (new_relative <= t) {
                index_intersected_primitive = k;
                t = new_relative;
            }
        }
        ++k;
    }
    if(found_intersection)
    {
        const std::shared_ptr<Rectangle>& rectangle = m_listRectangle[index_intersected_primitive];
        rectangle->intersect(ray, intersection);
    }
    return found_intersection;
}

}

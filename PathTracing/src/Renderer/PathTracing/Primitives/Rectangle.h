#include "Primitive.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H


namespace PathTracing
{
class Rectangle : public Primitive
{

public:
    Rectangle(glm::vec3 const& p_param,glm::vec3 const& v1_param,glm::vec3 const& v2_param);

    /*Return the point of the Rectangle*/
    glm::vec3 const& p() const;

    /*Return the two vectors*/
    glm::vec3 const& v1() const;
    glm::vec3 const& v2() const;


    /*Return normal of the Rectangle*/
    glm::vec3 const& normal() const;

    bool intersect(Ray const& ray_param,IntersectData& intersection) const;


private:
    glm::vec3 p_data;
    glm::vec3 v1_data;
    glm::vec3 v2_data;
    glm::vec3 normal_data;

};


}


#endif // RECTANGLE_H

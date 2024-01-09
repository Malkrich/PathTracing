#include "Primitive.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H


namespace PathTracing
{
class Rectangle : public Primitive
{

public:
    Rectangle(glm::vec3 const& p0_param,glm::vec3 const& p1_param,glm::vec3 const& normal_param);

    /*Return the 2 points (corners) of the Rectangle*/
    glm::vec3 const& p0() const;
    glm::vec3 const& p1() const;


    /*Return normal of the Rectangle*/
    glm::vec3 const& normal() const;

private:
    glm::vec3 p0_data;
    glm::vec3 p1_data;
    glm::vec3 normal_data;

};


}


#endif // RECTANGLE_H

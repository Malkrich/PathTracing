#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"

namespace PathTracing
{

/** Storage of a camera and screen parameters */
class Camera
{
public:

    // ********************************************* //
    //  Constructor
    // ********************************************* //

    Camera();

    /** Camera parameterized by its center, its main direction, and its up direction,
            the distance between the screen and the center, and the length of the screen */
    Camera(glm::vec3 const& center_param,
           glm::vec3 const& direction_param,
           glm::vec3 const& up_param,
           float distance_screen_param,
           float length_screen_param);

    // ********************************************* //
    //  Access parameters
    // ********************************************* //

    /** Get the center of the camera */
    glm::vec3 const& center() const;
    /** Get the direction value */
    glm::vec3 const& direction() const;
    /** Get the up direction value */
    glm::vec3 const& up() const;
    /** Get the dist_screen value */
    float distance_screen() const;
    /** Get the length_of the screen value */
    float length_screen() const;

    float getAspectRatio() const;
    void resize(unsigned int width, unsigned int height);

private:

    /** Internal camera center */
    glm::vec3 m_center;
    /** Direction of pointing camera */
    glm::vec3 m_direction;
    /** Up direction of the camera */
    glm::vec3 m_up;
    /** Internal screen distance to the center */
    float m_screenDistance;
    /** Length of the screen */
    float m_screenLength;
    /** aspect ration of the screen */
    float m_aspectRatio;
};

/** Compute the 3D position of the pixel parameterized by (u,v), where (u,v) is in [0,1] on the screen of the camera */
glm::vec3 screen_position(Camera const& cam,float u,float v);


}

#endif


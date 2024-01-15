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



    private:

        /** Internal camera center */
        glm::vec3 center_data;
        /** Direction of pointing camera */
        glm::vec3 direction_data;
        /** Up direction of the camera */
        glm::vec3 up_data;
        /** Internal screen distance to the center */
        float distance_screen_data;
        /** Length of the screen */
        float length_screen_data;
};

/** Compute the 3D position of the pixel parameterized by (u,v), where (u,v) is in [0,1] on the screen of the camera */
glm::vec3 screen_position(Camera const& cam,float u,float v);


}

#endif


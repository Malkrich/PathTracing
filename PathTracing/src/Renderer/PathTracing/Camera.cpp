#include "Camera.h"


namespace PathTracing
{

Camera::Camera()
    :center_data(glm::vec3(0.0f,0.0f,-2.0f)),
      direction_data(glm::vec3(0.0f,0.0f,1.0f)),
      up_data(glm::vec3(0.0f,1.0f,0.0f)),
      distance_screen_data(2.0f),
      length_screen_data(4.0f)
{}

Camera::Camera(glm::vec3 const& center_param,
       glm::vec3 const& direction_param,
       glm::vec3 const& up_param,
       float const distance_screen_param,
       float const length_screen_param)
    :center_data(center_param),
      direction_data(direction_param),
      up_data(up_param),
      distance_screen_data(distance_screen_param),
      length_screen_data(length_screen_param)
{}


glm::vec3 const& Camera::center() const {return center_data;}
glm::vec3 const& Camera::direction() const {return direction_data;}
glm::vec3 const& Camera::up() const {return up_data;}
float Camera::distance_screen() const {return distance_screen_data;}
float Camera::length_screen() const {return length_screen_data;}


glm::vec3 screen_position(Camera const& cam,float u,float v)
{

    glm::vec3 const right = glm::normalize(cross(cam.direction(),cam.up()));
    glm::vec3 const p0    = cam.center() + cam.direction() * cam.distance_screen();

    glm::vec3 const translate_right = right * (u-0.5f)*2.0f*cam.length_screen();
    glm::vec3 const translate_up    = cam.up() * (v-0.5f)*2.0f*cam.length_screen();

    glm::vec3 const current = p0+translate_right+translate_up;

    return current;
}

}

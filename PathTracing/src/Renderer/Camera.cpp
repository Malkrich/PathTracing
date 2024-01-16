#include "Camera.h"


namespace PathTracing
{

Camera::Camera()
    : Camera(glm::vec3(0.0f,0.0f,-2.0f),
             glm::vec3(0.0f,0.0f,1.0f),
             glm::vec3(0.0f,1.0f,0.0f),
             2.0f,
             4.0f)
{}

Camera::Camera(glm::vec3 const& center_param,
               glm::vec3 const& direction_param,
               glm::vec3 const& up_param,
               float const distance_screen_param,
               float const length_screen_param)
    : m_center(center_param)
    , m_direction(direction_param)
    , m_up(glm::normalize(up_param))
    , m_screenDistance(distance_screen_param)
    , m_screenLength(length_screen_param)
{}

glm::vec3 const& Camera::center() const {return m_center;}
glm::vec3 const& Camera::direction() const {return m_direction;}
glm::vec3 const& Camera::up() const {return m_up;}
float Camera::distance_screen() const {return m_screenDistance;}
float Camera::length_screen() const {return m_screenLength;}

float Camera::getAspectRatio() const { return m_aspectRatio; }
void Camera::resize(unsigned int width, unsigned int height)
{
    m_aspectRatio = (float)width / (float)height;
}

glm::vec3 screen_position(Camera const& cam,float u,float v)
{
    glm::vec3 const right = glm::normalize(cross(cam.direction(),cam.up()));
    glm::vec3 const p0    = cam.center() + cam.direction() * cam.distance_screen();

    glm::vec3 const translate_right = right * (u-0.5f)*2.0f*cam.getAspectRatio();
    glm::vec3 const translate_up    = cam.up() * (v-0.5f)*2.0f;

    glm::vec3 const current = p0+translate_right+translate_up;

    return current;
}

}

#include "Pch.h"

#include "Camera.h"

#include <glm/gtx/transform.hpp>

namespace PathTracing
{

    Camera::Camera(uint32_t width, uint32_t height)
        : m_width(width)
        , m_height(height)
    {
        // TEMP
        m_position = { 0.0f, 0.0f, 2.0f };
        m_forwardDirection = { 0.0f, 0.0f, -1.0f };

        recalculateViewMatrices();
        recalculateProjectionMatrices();
        recalculateRayDirections();
    }

    void Camera::onResize(uint32_t width, uint32_t height)
    {
        if (m_width == width && m_height == height)
            return;

        m_width = width;
        m_height = height;

        recalculateProjectionMatrices();
        recalculateRayDirections();
    }


    void Camera::onUpdate(float dt)
    {

    }

    void Camera::recalculateViewMatrices()
    {
        constexpr glm::vec3 upVector = { 0.0f, 1.0f, 0.0f };
        m_viewMatrix = glm::lookAt(m_position, m_position + m_forwardDirection, upVector);
        m_inverseViewMatrix = glm::inverse(m_viewMatrix);
    }

    void Camera::recalculateProjectionMatrices()
    {
        m_projectionMatrix = glm::perspectiveFov(glm::radians(m_fov), (float)m_width, (float)m_height, m_nearClip, m_farClip);
        m_inverseProjectionMatrix = glm::inverse(m_projectionMatrix);
    }

    void Camera::recalculateRayDirections()
    {
        m_rayDirections.resize(m_width * m_height);

        for (uint32_t y = 0; y < m_height; y++)
        {
            for (uint32_t x = 0; x < m_width; x++)
            {
                // Pixel coord from 0.0 to 1.0
                glm::vec2 coord = { (float)x / (float)m_width, (float)y / (float)m_height };
                // Pixel coord from -1.0f to 1.0
                coord = coord * 2.0f - 1.0f;

                // Transform ray direction from screen space to view space
                glm::vec4 target = m_inverseProjectionMatrix * glm::vec4(coord.x, coord.y, 1, 1);
                // Transform ray direction from view space to world space
                glm::vec3 rayDirection = glm::vec3(m_inverseViewMatrix * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space
                m_rayDirections[x + y * m_width] = rayDirection;
            }
        }
    }

}

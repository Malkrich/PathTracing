#include "Pch.h"

#include "Camera.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace PathTracing
{

    Camera::Camera(uint32_t width, uint32_t height)
        : m_width(width)
        , m_height(height)
        , m_mousePosition(Input::getMousePosition())
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


    void Camera::toggleCameraLocking()
    {
        m_cameraControlLocked = !m_cameraControlLocked;
        Input::setCursorMode(m_cameraControlLocked ? CursorMode::Locked : CursorMode::Normal);
    }

    bool Camera::onUpdate(float dt)
    {
        bool cameraMoved = false;

        glm::vec3 rightDirection = glm::cross(m_forwardDirection, m_upDirection);

        glm::ivec2 currentMousePos = Input::getMousePosition();
        glm::ivec2 mouseOffset = currentMousePos - m_mousePosition;
        m_mousePosition = currentMousePos;

        if (m_cameraControlLocked && mouseOffset.x != 0 && mouseOffset.y != 0)
        {
            float pitchOffset = (float)mouseOffset.y * m_rotationSpeed;
            float yawOffset   = (float)mouseOffset.x * m_rotationSpeed;

            glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchOffset, rightDirection),
                glm::angleAxis(-yawOffset, m_upDirection)));
            m_forwardDirection = glm::rotate(q, m_forwardDirection);

            cameraMoved = true;
        }

        if (Input::isKeyPressed(PT_KEY_W))
        {
            m_position += m_forwardDirection * m_translationSpeed * dt;
            cameraMoved = true;
        }
        if (Input::isKeyPressed(PT_KEY_S))
        {
            m_position -= m_forwardDirection * m_translationSpeed * dt;
            cameraMoved = true;
        }
        if (Input::isKeyPressed(PT_KEY_A))
        {
            m_position -= rightDirection * m_translationSpeed * dt;
            cameraMoved = true;
        }
        if (Input::isKeyPressed(PT_KEY_D))
        {
            m_position += rightDirection * m_translationSpeed * dt;
            cameraMoved = true;
        }
        if (Input::isKeyPressed(PT_KEY_SPACE))
        {
            m_position += m_upDirection * m_translationSpeed * dt;
            cameraMoved = true;
        }
        if (Input::isKeyPressed(PT_KEY_LEFT_SHIFT))
        {
            m_position -= m_upDirection * m_translationSpeed * dt;
            cameraMoved = true;
        }

        if (cameraMoved)
        {
            recalculateViewMatrices();
            recalculateRayDirections();
        }

        return cameraMoved;
    }

    void Camera::recalculateViewMatrices()
    {
        m_viewMatrix = glm::lookAt(m_position, m_position + m_forwardDirection, m_upDirection);
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

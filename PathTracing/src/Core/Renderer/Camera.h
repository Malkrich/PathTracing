#pragma once

#include <glm/glm.hpp>

namespace PathTracing
{

    // From: https://github.com/TheCherno/RayTracing/blob/master/RayTracing/src/Camera.cpp
    class Camera
    {
    public:
        Camera(uint32_t width, uint32_t height);

        void onResize(uint32_t width, uint32_t height);
        bool onUpdate(float dt);

        const glm::vec3& getPosition() const { return m_position; }
        const std::vector<glm::vec3>& getRayDirections() const { return m_rayDirections; }

    private:
        void recalculateViewMatrices();
        void recalculateProjectionMatrices();
        void recalculateRayDirections();

    private:
        glm::mat4 m_viewMatrix{ 1.0f };
        glm::mat4 m_inverseViewMatrix{ 1.0f };
        glm::mat4 m_projectionMatrix{ 1.0f };
        glm::mat4 m_inverseProjectionMatrix{ 1.0f };

        std::vector<glm::vec3> m_rayDirections;

        glm::vec3 m_position{ 0.0f };
        glm::vec3 m_forwardDirection{ 0.0f };
        glm::vec3 m_rightDirection{ 0.0f };
        glm::vec3 m_upVector = { 0.0f, 1.0f, 0.0f };

        float m_fov = 45.0f;
        float m_nearClip = 0.1f, m_farClip = 1000.0f;

        uint32_t m_width = 0, m_height = 0;

        float m_translationSpeed = 1.0f;
    };

}
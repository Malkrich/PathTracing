#include "Pch.h"

#include "ViewportPanel.h"

#include <imgui.h>
#include <glad/glad.h>

namespace PathTracing
{

    ViewportPanel::ViewportPanel()
        : m_width(0)
        , m_height(0)
    {
        m_viewportTexture = std::make_unique<Texture>();
    }

    void ViewportPanel::setViewportImageData(const void* imageData)
    {
        m_viewportTexture->bind();
        m_viewportTexture->setData(m_width, m_height, imageData);
    }

    void ViewportPanel::onGuiRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("Viewport", nullptr);
        m_width     = ImGui::GetContentRegionAvail().x;
        m_height    = ImGui::GetContentRegionAvail().y;
        ImGui::Image((void*)m_viewportTexture->getTextureId(), ImVec2(m_width, m_height), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();

        ImGui::PopStyleVar(3);
    }

}

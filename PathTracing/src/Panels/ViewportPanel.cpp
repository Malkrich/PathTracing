#include "Pch.h"

#include "ViewportPanel.h"

#include <imgui.h>
#include <glad/glad.h>

namespace PathTracing
{

    ViewportPanel::ViewportPanel(uint32_t width, uint32_t height)
    {
        m_viewportTexture = std::make_unique<Texture>(width, height);
    }

    void ViewportPanel::setViewportImageData(const void* imageData)
    {
        m_viewportTexture->bind();
        m_viewportTexture->setData(imageData);
    }

    void ViewportPanel::onGuiRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("Viewport", nullptr);
        uint32_t width  = ImGui::GetContentRegionAvail().x;
        uint32_t height = ImGui::GetContentRegionAvail().y;

        ImGui::Image((void*)m_viewportTexture->getTextureId(), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));
        m_viewportTexture->resize(width, height);

        ImGui::End();

        ImGui::PopStyleVar(3);
    }

}

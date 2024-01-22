#include "Viewport.h"

#include <imgui.h>
#include <glad/glad.h>

namespace PathTracing
{

Viewport::Viewport()
    : m_width(0)
    , m_height(0)
{
    m_viewportTexture.reset(new Texture());
}

void Viewport::setViewportImage(const std::shared_ptr<Image>& image)
{
    m_viewportTexture->bind();
    m_viewportTexture->setData(image);
}

void Viewport::onViewportRender()
{
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    m_width     = ImGui::GetContentRegionAvail().x;
    m_height    = ImGui::GetContentRegionAvail().y;
    ImGui::Image(reinterpret_cast<void*>(m_viewportTexture->getTextureId()),
                 ImVec2(m_width, m_height), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

}

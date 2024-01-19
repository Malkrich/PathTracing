#include "Editor.h"

#include <iostream>
#include <string>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Base.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include "Renderer/PathTracing/PathTracer.h"
#include "Renderer/Primitives/Plane.h"
#include "Renderer/Primitives/Rectangle.h"
#include "Renderer/Primitives/Sphere.h"
#include "Renderer/PathTracing/Materials/Lambertian.h"
#include "Renderer/PathTracing/Materials/Light.h"
#include "Renderer/Camera.h"

namespace PathTracing
{

void createCornellBoxScene(std::shared_ptr<SceneData> scene)
{
    /***** CORNELL BOX ****/
    glm::vec3 red = glm::vec3(1,.05,.05);
    glm::vec3 green = glm::vec3(.12,1,.15);
    glm::vec3 light = glm::vec3(1,1,1);
    glm::vec3 white = glm::vec3(.73,.73,.73);
    glm::vec3 blue = glm::vec3(.05,.05,1);

    scene->addRectangle("Green Rectangle",
                        glm::vec3(1.0f,-1.0f,0.0f), glm::vec3(0,0,1), glm::vec3(0,2,0),
                        SceneObjectMaterial::lambertien, green);
    scene->addRectangle("Red Rectangle",
                        glm::vec3(-1.0f,-1.0f,0.0f), glm::vec3(0,2.00f,0), glm::vec3(0,0,1.00f),
                        SceneObjectMaterial::lambertien, red);
    scene->addRectangle("Light",
                        glm::vec3(0.2,0.99,0.3),glm::vec3(-0.4,0,0),glm::vec3(0,0,0.4),
                        SceneObjectMaterial::light, light);
    scene->addRectangle("White Rectangle 1",
                        glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(-2.00f,0,0),glm::vec3(0,0,1.00f),
                        SceneObjectMaterial::lambertien, white);
    scene->addRectangle("White Rectangle 2",
                        glm::vec3(1.00f,1.00f,0.00f),glm::vec3(0,0,1.00f),glm::vec3(-2.00f,0,0),
                        SceneObjectMaterial::lambertien, white);
    scene->addRectangle("Blue Rectangle",
                        glm::vec3(1,-1,1),glm::vec3(-2,0,0),glm::vec3(0,2,0),
                        SceneObjectMaterial::lambertien, blue);
    scene->addSphere("Sphere",
                     glm::vec3(0.0f, 0.3f, 0.7f), 0.3f,
                     SceneObjectMaterial::lambertien, glm::vec3(1.0f, 0.0f, 0.0f));

    RenderSettings renderSettings;
    renderSettings.samplePerPixel = 1;
    renderSettings.maxDepth = 2;
    scene->setRenderSettings(renderSettings);
}

Editor::Editor()
{
    m_sceneData.reset(new SceneData());
    createCornellBoxScene(m_sceneData);
}

void Editor::makeSlider1(const std::string& name, const std::string& sliderName, float* value, float min, float max)
{
    float width = ImGui::GetContentRegionAvail().x;
    std::string sliderHiddenName = "##" + sliderName;

    ImGui::Text("%s", name.c_str());
    ImGui::PushItemWidth(m_guiLayoutSettings.sliderWidth);
    ImGui::SameLine(width - m_guiLayoutSettings.sliderWidth);
    ImGui::SliderFloat(sliderHiddenName.c_str(), value, min, max);
    ImGui::PopItemWidth();
}

void Editor::makeSlider2(const std::string& name, const std::string& sliderName, const glm::vec2& value, float min, float max)
{
    float width = ImGui::GetContentRegionAvail().x;
    std::string sliderHiddenName = "##" + sliderName;

    ImGui::Text("%s", name.c_str());
    ImGui::PushItemWidth(m_guiLayoutSettings.sliderWidth);
    ImGui::SameLine(width - m_guiLayoutSettings.sliderWidth);
    ImGui::SliderFloat2(sliderHiddenName.c_str(), (float*)glm::value_ptr(value), min, max);
    ImGui::PopItemWidth();
}

void Editor::makeSlider3(const std::string& name, const std::string& sliderName, const glm::vec3& value, float min, float max)
{
    float width = ImGui::GetContentRegionAvail().x;
    std::string sliderHiddenName = "##" + sliderName;

    ImGui::Text("%s", name.c_str());
    ImGui::PushItemWidth(m_guiLayoutSettings.sliderWidth);
    ImGui::SameLine(width - m_guiLayoutSettings.sliderWidth);
    ImGui::SliderFloat3(sliderHiddenName.c_str(), (float*)glm::value_ptr(value), min, max);
    ImGui::PopItemWidth();
}

void Editor::makeColorPicker3(const std::string& name, const std::string& colorPickerName, const glm::vec3& value)
{
    float width = ImGui::GetContentRegionAvail().x;
    std::string colorPickerHiddenName = "##" + colorPickerName;

    ImGui::Text("%s", name.c_str());
    ImGui::SameLine(width - m_guiLayoutSettings.colorPickerWidth);
    ImGui::PushItemWidth(m_guiLayoutSettings.colorPickerWidth);
    ImGui::ColorEdit3(colorPickerHiddenName.c_str(), (float*)glm::value_ptr(value),
                      ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
    ImGui::PopItemWidth();
}

void Editor::makeInputInt1(const std::string& name, const std::string& inputIntName, int *value)
{
    float width = ImGui::GetContentRegionAvail().x;
    std::string inputIntHiddenName = "##" + inputIntName;

    ImGui::Text("%s", name.c_str());
    ImGui::SameLine(width - m_guiLayoutSettings.inputValueWidth);
    ImGui::PushItemWidth(m_guiLayoutSettings.inputValueWidth);
    ImGui::InputInt(inputIntHiddenName.c_str(), value);
    ImGui::PopItemWidth();
}

void Editor::makeGuiForResetButton(const std::string& name, void(*resetFunction)(SceneData&))
{
    std::string fullName = "Reset##" + name;
    float width = ImGui::GetContentRegionAvail().x;
    ImGui::Indent(width - m_guiLayoutSettings.resetButtonWidth);
    if(ImGui::Button(fullName.c_str(), ImVec2(m_guiLayoutSettings.resetButtonWidth, 20)))
        resetFunction(*m_sceneData);
    ImGui::Unindent(width - m_guiLayoutSettings.resetButtonWidth);
}

void Editor::makeGuiForSceneObject(const SceneObjectData& sceneObject)
{
    const std::string& name = sceneObject.name;
    ImGui::Text("%s", name.c_str());

//    int current
    const char* items[] = { "Plane",
                            "Rectangle",
                            "Sphere"};
    static const unsigned int itemCount = 3;
    int currentItem = 0;
//    ImGui::Combo("##Primitive", &currentItem, items, itemCount);

    // Color
    makeColorPicker3("Color :", sceneObject.name, sceneObject.color);
    // Position
    makeSlider3("Position :", sceneObject.name, sceneObject.primitive->getPosition(), -2.0f, 2.0f);
}

void Editor::onGuiRender()
{
    ImGui::Begin("Scene");

    // Camera
    ImGui::SeparatorText("Camera :");
    makeGuiForResetButton("CameraReset", [](SceneData& sceneData)
    {
        CameraData camera;
        sceneData.setCameraData(camera);
    });
    makeSlider3("Position :", "CameraPosition", m_sceneData->getCameraData().position, -5.0f, 5.0f);
    makeSlider2("Direction :", "CameraDirection", m_sceneData->getCameraData().direction, -1.0f, 1.0f);
    makeSlider1("Screen Distance :", "CameraScreenDistance", (float*)&(m_sceneData->getCameraData().screenDistance), 0.0f, 5.0f);

    ImGui::SeparatorText("Scene Hierarchy :");
    for(auto& sceneObject : *m_sceneData)
    {
        makeGuiForSceneObject(sceneObject);
        ImGui::Separator();
    }
    ImGui::SeparatorText("Render Settings :");
    makeGuiForResetButton("RenderingParameterReset", [](SceneData& sceneData)
    {
        RenderSettings renderSettings;
        sceneData.setRenderSettings(renderSettings);
    });
    makeInputInt1("Sample Per Pixel :", "SamplePerPixel", (int*)&m_sceneData->getRenderSettings().samplePerPixel);
    makeInputInt1("Maximum Depth :", "MaxDepth", (int*)&m_sceneData->getRenderSettings().maxDepth);

    ImGui::End();
}

}

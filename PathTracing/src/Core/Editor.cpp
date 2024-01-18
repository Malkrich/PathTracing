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

void Editor::makeGuiForResetButton(const std::string& name, void(*resetFunction)(SceneData&))
{
    std::string fullName = "Reset##" + name;
    float width = ImGui::GetWindowWidth();
    ImGui::Indent(width - m_guiLayoutSettings.resetButtonOffset);
    if(ImGui::Button(fullName.c_str(), ImVec2(70, 20)))
        resetFunction(*m_sceneData);
    ImGui::Unindent(width - m_guiLayoutSettings.resetButtonOffset);
}

void Editor::makeGuiForSceneObject(const SceneObjectData& sceneObject)
{
    const std::string& name = sceneObject.name;
    std::string positionName = "##" + name;
    ImGui::Text("%s", name.c_str());

    // Color
    ImGui::Text("Color : ");
    ImGui::SameLine(m_guiLayoutSettings.parameterOffset);
    ImGui::ColorEdit3(name.c_str(), (float*)glm::value_ptr(sceneObject.color),
                      ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

    // Position
    ImGui::Text("Position : ");
    ImGui::SameLine(m_guiLayoutSettings.parameterOffset);
    ImGui::SliderFloat3(positionName.c_str(), (float*)glm::value_ptr(sceneObject.primitive->getPosition()),
                        -2.0f, 2.0f);
}

void Editor::onGuiRender()
{
//    ImGui::Begin("Info : ", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
//    ImGui::SetWindowSize(ImVec2(250, 110));
//    ImGui::SeparatorText("Renderer info :");
//    ImGui::Text("Delta time : %f ms", m_deltaTime * 1000.0f);
//    ImGui::Text("Fps : %f", 1 / m_deltaTime);
//    ImGui::Text("");
//    ImGui::Text("Window dimension : [%i , %i]",
//                Renderer::getViewportWidth(), Renderer::getViewportHeight());
//    ImGui::End();

    ImGui::Begin("Scene");
    ImGui::SeparatorText("Camera :");
    makeGuiForResetButton("##CameraReset", [](SceneData& sceneData)
    {
        CameraData camera;
        sceneData.setCameraData(camera);
    });
    ImGui::Text("Position");
    ImGui::SameLine(m_guiLayoutSettings.parameterOffset);
    ImGui::SliderFloat3("##CameraPosition", (float*)glm::value_ptr(m_sceneData->getCameraData().position),
                        -5.0f, 5.0f);
    ImGui::Text("Direction");
    ImGui::SameLine(m_guiLayoutSettings.parameterOffset);
    ImGui::SliderFloat2("##CameraDirection", (float*)glm::value_ptr(m_sceneData->getCameraData().direction),
                        -1.0f, 1.0f);
    ImGui::Text("Screen Distance");
    ImGui::SameLine(m_guiLayoutSettings.parameterOffset);
    ImGui::SliderFloat("##CameraScreenDistance", (float*)&(m_sceneData->getCameraData().screenDistance),
                       0.0f, 5.0f);
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
    ImGui::Text("Sample Per Pixel");
    ImGui::SameLine(m_guiLayoutSettings.parameterOffset);
    ImGui::InputInt("##SamplePerPixel", (int*)(&m_sceneData->getRenderSettings().samplePerPixel));
    ImGui::Text("Max Depth");
    ImGui::SameLine(m_guiLayoutSettings.parameterOffset);
    ImGui::InputInt("##MaxDepth", (int*)(&m_sceneData->getRenderSettings().maxDepth));
    ImGui::End();
}

}

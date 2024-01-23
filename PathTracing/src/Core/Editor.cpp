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
#include "Renderer/Primitives/Box.h"
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
    glm::vec3 light = glm::vec3(50,50,50);
    glm::vec3 white = glm::vec3(.73,.73,.73)*10.0f;
    glm::vec3 blue = glm::vec3(.05,.05,1);
    glm::vec3 one = glm::vec3(1,1,1);

    scene->addRectangle("Green Rectangle",
                        glm::vec3(1.0f,-1.0f,0.0f), glm::vec3(0,0,1), glm::vec3(0,2,0),
                        std::make_shared<LambertianData>(green));
    scene->addRectangle("Red Rectangle",
                        glm::vec3(-1.0f,-1.0f,0.0f), glm::vec3(0,2.00f,0), glm::vec3(0,0,1.00f),
                        std::make_shared<LambertianData>(red));
    scene->addRectangle("Light",
                        glm::vec3(0.2,0.99,0.3),glm::vec3(-0.4,0,0),glm::vec3(0,0,0.4),
                        std::make_shared<LightData>(light));
    scene->addRectangle("White Rectangle 1",
                        glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(-2.00f,0,0),glm::vec3(0,0,1.00f),
                        std::make_shared<LambertianData>(white));
    scene->addRectangle("White Rectangle 2",
                        glm::vec3(1.00f,1.00f,0.00f),glm::vec3(0,0,1.00f),glm::vec3(-2.00f,0,0),
                        std::make_shared<LambertianData>(white));
    scene->addRectangle("Blue Rectangle",
                        glm::vec3(1,-1,1),glm::vec3(-2,0,0),glm::vec3(0,2,0),
                        std::make_shared<LambertianData>(blue));
    scene->addSphere("Sphere",
                     glm::vec3(0.0f, 0.0f, 0.7f), 0.5f,
                     std::make_shared<LambertianData>(glm::vec3(0.7f, 0.5f, 0.5f)));
    scene->addRectangle("Light 2",
                        glm::vec3(0.2,-0.99,0.3),glm::vec3(-0.4,0,0),glm::vec3(0,0,0.4),
                        std::make_shared<LightData>(light));
//    scene->addRectangle("Mirror",
//                        glm::vec3(0.500,-0.0,0.666),glm::vec3(-0.4,0,0.4),glm::vec3(0,0.5,0.0),
//                        std::make_shared<MirrorData>(white));
    scene->addBox("box",
                            glm::vec3(0.5,0.8,0.7),glm::vec3(0.5,0.8,0.7)+glm::vec3(0.3,0.3,0.3),
                            std::make_shared<LambertianData>(red));

    RenderSettings renderSettings;
    renderSettings.samplePerPixel = 1;
    renderSettings.maxDepth = 10;
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

void Editor::makeCombo(const std::string& name, const std::string& comboName,
                       const std::vector<const char*>& itemList, int currentItem,
                       void (*comboboxCallback)(int, SceneObjectData&), SceneObjectData& sceneObject)
{
    const int itemCount = itemList.size();
    float width = ImGui::GetContentRegionAvail().x;

    ImGui::Text("%s", name.c_str());
    ImGui::SameLine(width - m_guiLayoutSettings.comboWidth);
    ImGui::PushItemWidth(m_guiLayoutSettings.comboWidth);
    if(ImGui::Combo(comboName.c_str(), &currentItem, itemList.data(), itemCount))
        comboboxCallback(currentItem, sceneObject);
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

void Editor::makeGuiForSceneObject(SceneObjectData& sceneObject)
{
    const std::string& name = sceneObject.name;
    const std::string primitiveHiddenName   = "##" + name + "_primitive";
    const std::string materialHiddenName    = "##" + name + "_material";
    ImGui::Text("%s", name.c_str());

    // Primitive
    {
        int currentItem = (int)sceneObject.primitive->getPrimitiveType();
        makeCombo("Primitive :", primitiveHiddenName,
                  {"Plane", "Rectangle", "Sphere", "Box"}, currentItem,
                  [](int currentItem, SceneObjectData& sceneObject)
        {
            sceneObject.primitive = PrimitiveData::create( (SceneObjectPrimitive)currentItem );
        }, sceneObject);
    }
    makeGuiForPrimitive(name, sceneObject.primitive);

    // Material
    {
        int currentItem = (int)sceneObject.material->getMaterialType();
        makeCombo("Material :", materialHiddenName,
                  {"Lambertian", "Light", "Mirror"}, currentItem,
                  [](int currentItem, SceneObjectData& sceneObject)
        {
            sceneObject.material = MaterialData::create( (SceneObjectMaterial)currentItem );
        }, sceneObject);
    }
    makeColorPicker3("Color :", sceneObject.name, sceneObject.material->getColor());
}

void Editor::makeGuiForPrimitive(const std::string& name, std::shared_ptr<PrimitiveData> primitiveData)
{
    SceneObjectPrimitive primitiveType = primitiveData->getPrimitiveType();

    std::string positionName = name + "_position";
    makeSlider3("Position :", positionName, primitiveData->getPosition(), -5.0f, 5.0f);

    switch(primitiveType)
    {
        case SceneObjectPrimitive::plane:
        {
            std::shared_ptr<PlaneData> plane = std::static_pointer_cast<PlaneData>(primitiveData);
            std::string normalName = name + "_normal";
            makeSlider3("Normal :", normalName, plane->getNormal(), -1.0f, 1.0f);
            break;
        }
        case SceneObjectPrimitive::rectangle:
        {
            std::shared_ptr<RectangleData> rectangle = std::static_pointer_cast<RectangleData>(primitiveData);
            std::string v1Name = name + "_v1";
            std::string v2Name = name + "_v2";
            makeSlider3("V1 :", v1Name, rectangle->getV1(), -5.0f, 5.0f);
            makeSlider3("V2 :", v2Name, rectangle->getV2(), -5.0f, 5.0f);
            break;
        }
        case SceneObjectPrimitive::sphere:
        {
            std::shared_ptr<SphereData> sphere = std::static_pointer_cast<SphereData>(primitiveData);
            std::string radiusName = name + "_radius";
            makeSlider1("Radius :", radiusName, (float*)&sphere->getRadius(), 0.0f, 5.0f);
            break;
        }
        case SceneObjectPrimitive::box:
        {
            std::shared_ptr<BoxData> box = std::static_pointer_cast<BoxData>(primitiveData);
            std::string p2Name = name + "_p2";
            makeSlider3("P2 :", p2Name, box->getP2(), -5.0f, 5.0f);
            break;
        }
    }
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
    ImGui::End();

    ImGui::Begin("Renderer");
    ImGui::SeparatorText("Render Settings :");
    makeGuiForResetButton("RenderingParameterReset", [](SceneData& sceneData)
    {
        RenderSettings renderSettings;
        sceneData.setRenderSettings(renderSettings);
    });
    makeInputInt1("Sample Per Pixel :", "SamplePerPixel", (int*)&m_sceneData->getRenderSettings().samplePerPixel);
    makeInputInt1("Maximum Depth :", "MaxDepth", (int*)&m_sceneData->getRenderSettings().maxDepth);
    ImGui::SeparatorText("Statistic :");
    ImGui::Text("Render duration : %.3f s", m_renderDuration);
    ImGui::End();
}

}

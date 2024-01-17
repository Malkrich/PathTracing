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
        glm::vec3 red = glm::vec3(.65,.05,.05);
        glm::vec3 green = glm::vec3(.12,.45,.15);
        glm::vec3 light = glm::vec3(1,1,1);
        glm::vec3 white = glm::vec3(.73,.73,.73);
        glm::vec3 blue = glm::vec3(.05,.05,.65);

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

        RenderSettings renderSettings;
        renderSettings.samplePerPixel = 2;
        renderSettings.maxDepth = 5;
        scene->setRenderSettings(renderSettings);

//        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(-25.0f,20.0f,50.0f),3);//1.9999
//        std::shared_ptr<Lambertian> l7 = std::make_shared<Lambertian>(red);
//        std::shared_ptr<SceneObject> so7 = std::make_shared<SceneObject>(sphere,l7);
//        m_scene->addObject(so7);
    }

	Editor::Editor()
	{
        m_sceneData.reset(new SceneData());
        createCornellBoxScene(m_sceneData);
    }

	void Editor::onUpdate(float dt)
	{
        m_deltaTime = dt;
	}

	void Editor::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Editor::onWindowResizeEvent));
	}

	bool Editor::onWindowResizeEvent(const WindowResizeEvent& e)
	{
		Renderer::resize(e.getWidth(), e.getHeight());
		return true;
	}

    void Editor::makeGuiForSceneObject(const SceneObjectData& sceneObject)
    {
        const std::string& name = sceneObject.name;
        std::string positionName = "##" + name;
        ImGui::Text("%s", name.c_str());

        // Color
        ImGui::Text("Color : ");
        ImGui::SameLine(m_guiLayoutSettings.m_editorSpace);
        ImGui::ColorEdit3(name.c_str(), (float*)glm::value_ptr(sceneObject.color),
                          ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

        // Position
        ImGui::Text("Position : ");
        ImGui::SameLine(m_guiLayoutSettings.m_editorSpace);
        ImGui::SliderFloat3(positionName.c_str(), (float*)glm::value_ptr(sceneObject.primitive->getPosition()),
                            -2.0f, 2.0f, "%.3f");
    }

	void Editor::onGuiRender()
	{
        ImGui::Begin("Info : ", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowSize(ImVec2(250, 110));
        ImGui::SeparatorText("Renderer info :");
        ImGui::Text("Delta time : %f ms", m_deltaTime * 1000.0f);
        ImGui::Text("Fps : %f", 1 / m_deltaTime);
        ImGui::Text("");
        ImGui::Text("Window dimension : [%i , %i]",
                    Renderer::getViewportWidth(), Renderer::getViewportHeight());
		ImGui::End();

        ImGui::Begin("Scene");
        ImGui::SeparatorText("Scene Hierarchy :");
        for(auto& sceneObject : *m_sceneData)
        {
            makeGuiForSceneObject(sceneObject);
            ImGui::Separator();
        }
        ImGui::SeparatorText("Render Settings :");
        ImGui::Text("Sample Per Pixel");
        ImGui::SameLine(m_guiLayoutSettings.m_editorSpace);
        ImGui::InputInt("##SamplePerPixel", (int*)(&m_sceneData->getRenderSettings().samplePerPixel));
        ImGui::Text("Max Depth");
        ImGui::SameLine(m_guiLayoutSettings.m_editorSpace);
        ImGui::InputInt("##MaxDepth", (int*)(&m_sceneData->getRenderSettings().maxDepth));
        ImGui::End();
	}

}

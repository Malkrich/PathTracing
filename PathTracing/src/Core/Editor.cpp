#include "Editor.h"

#include <iostream>
#include <string>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Base.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include "Renderer/Primitives/Plane.h"
#include "Renderer/Primitives/Rectangle.h"
#include "Renderer/Primitives/Sphere.h"
#include "Renderer/PathTracing/Materials/Lambertian.h"
#include "Renderer/PathTracing/Materials/Light.h"
#include "Renderer/Camera.h"

namespace PathTracing
{
    static void makeGuiForSceneObject(const SceneObject* sceneObject)
    {
        const std::string& name = sceneObject->getName();
        std::string positionName = "##" + name;
        glm::vec3& albedo = sceneObject->material->getAlbedo();
        glm::vec3& position = sceneObject->primitive->getPosition();
        ImGui::Text("%s", name.c_str());

        // Color
        ImGui::Text("Color : ");
        ImGui::SameLine();
        ImGui::ColorEdit3(name.c_str(), glm::value_ptr(albedo), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

        // Position
        ImGui::SliderFloat3(positionName.c_str(), glm::value_ptr(position), -2.0f, 2.0f, "%.3f");
    }

	Editor::Editor()
	{
		// has to be called first
		Renderer::init();

        m_image.reset(new Image32UI(Renderer::getViewportWidth(), Renderer::getViewportHeight()));

        m_scene.reset(new Scene());

        Camera cam = Camera();
        cam.resize(Renderer::getViewportWidth(), Renderer::getViewportHeight());
        m_scene->setCamera(cam);

        /***** CORNELL BOX ****/
        glm::vec3 red = glm::vec3(.65,.05,.05);
        glm::vec3 green = glm::vec3(.12,.45,.15);
        glm::vec3 light = glm::vec3(1,1,1);
        glm::vec3 white = glm::vec3(.73,.73,.73);
        glm::vec3 blue = glm::vec3(.05,.05,.65);

        Rectangle* r1 = new Rectangle(glm::vec3(1.0f,-1.0f,0.0f), glm::vec3(0,0,1), glm::vec3(0,2,0));
        Lambertian* l1 = new Lambertian(green);
        SceneObject* so1 = new SceneObject(r1, l1, "Green Rectangle");
        m_scene->addObject(so1);

        Rectangle* r2 = new Rectangle(glm::vec3(-1.0f,-1.0f,0.0f), glm::vec3(0,2.00f,0), glm::vec3(0,0,1.00f));
        Lambertian* l2 = new Lambertian(red);
        SceneObject* so2 = new SceneObject(r2, l2, "Red Rectangle");
        m_scene->addObject(so2);

        Rectangle* r3 = new Rectangle(glm::vec3(0.2,0.99,0.3),glm::vec3(-0.4,0,0),glm::vec3(0,0,0.4));
        Light* l3 = new Light(light);
        SceneObject* so3 = new SceneObject(r3, l3, "Light");
        m_scene->addObject(so3);

        Rectangle* r4 = new Rectangle(glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(-2.00f,0,0),glm::vec3(0,0,1.00f));
        Lambertian* l4 = new Lambertian(white);
        SceneObject* so4 = new SceneObject(r4, l4, "White Rectangle 1");
        m_scene->addObject(so4);

        Rectangle* r5 = new Rectangle(glm::vec3(1.00f,1.00f,0.00f),glm::vec3(0,0,1.00f),glm::vec3(-2.00f,0,0));
        Lambertian* l5 = new Lambertian(white);
        SceneObject* so5 = new SceneObject(r5, l5, "White Rectangle 2");
        m_scene->addObject(so5);

        Rectangle* r6 = new Rectangle(glm::vec3(1,-1,1),glm::vec3(-2,0,0),glm::vec3(0,2,0));
        Lambertian* l6 = new Lambertian(blue);
        SceneObject* so6 = new SceneObject(r6, l6, "Blue Rectangle");
        m_scene->addObject(so6);

//        Sphere* sphere = new Sphere(glm::vec3(-25.0f,20.0f,50.0f),3);//1.9999
//        Lambertian* l7 = new Lambertian(red);
//        SceneObject* so7 = new SceneObject(sphere,l7);
//        m_scene->addObject(so7);
	}

	Editor::~Editor()
	{
		Renderer::shutdown();
	}

	void Editor::onUpdate(float dt)
	{
		m_deltaTime = dt;
		// Renderer render
		Renderer::begin(m_clearColor);
        Renderer::pathTrace(m_image, m_scene);
		Renderer::draw(m_image);
	}

	void Editor::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Editor::onWindowResizeEvent));
	}

	bool Editor::onWindowResizeEvent(const WindowResizeEvent& e)
	{
		m_image->resize(e.getWidth(), e.getHeight());
		Renderer::resize(e.getWidth(), e.getHeight());
        m_scene->getCamera().resize(e.getWidth(), e.getHeight());
		return true;
	}

	void Editor::onGuiRender()
	{
        ImGui::Begin("Info : ", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowSize(ImVec2(250, 100));
        ImGui::Text("Renderer info : ");
        ImGui::Text("Delta time : %f ms", m_deltaTime * 1000.0f);
        ImGui::Text("Fps : %f", 1 / m_deltaTime);
        ImGui::Text("");
        ImGui::Text("Window dimension : [%i , %i]",
                    Renderer::getViewportWidth(), Renderer::getViewportHeight());
		ImGui::End();

        ImGui::Begin("Scene editor");
        for(auto& sceneObject : *m_scene)
        {
            makeGuiForSceneObject(sceneObject);
            ImGui::Separator();
        }
        ImGui::End();
	}

}

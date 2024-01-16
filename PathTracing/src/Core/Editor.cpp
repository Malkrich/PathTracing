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
    void createCornellBoxScene(std::shared_ptr<Scene> scene)
    {
        /***** CORNELL BOX ****/
        glm::vec3 red = glm::vec3(.65,.05,.05);
        glm::vec3 green = glm::vec3(.12,.45,.15);
        glm::vec3 light = glm::vec3(1,1,1);
        glm::vec3 white = glm::vec3(.73,.73,.73);
        glm::vec3 blue = glm::vec3(.05,.05,.65);

        std::shared_ptr<Rectangle> r1 = std::make_shared<Rectangle>(glm::vec3(1.0f,-1.0f,0.0f), glm::vec3(0,0,1), glm::vec3(0,2,0));
        std::shared_ptr<Lambertian> l1 = std::make_shared<Lambertian>(green);
        std::shared_ptr<SceneObject> so1 = std::make_shared<SceneObject>(r1, l1, "Green Rectangle");
        scene->addObject(so1);

        std::shared_ptr<Rectangle> r2 = std::make_shared<Rectangle>(glm::vec3(-1.0f,-1.0f,0.0f), glm::vec3(0,2.00f,0), glm::vec3(0,0,1.00f));
        std::shared_ptr<Lambertian> l2 = std::make_shared<Lambertian>(red);
        std::shared_ptr<SceneObject> so2 = std::make_shared<SceneObject>(r2, l2, "Red Rectangle");
        scene->addObject(so2);

        std::shared_ptr<Rectangle> r3 = std::make_shared<Rectangle>(glm::vec3(0.2,0.99,0.3),glm::vec3(-0.4,0,0),glm::vec3(0,0,0.4));
        std::shared_ptr<Light> l3 = std::make_shared<Light>(light);
        std::shared_ptr<SceneObject> so3 = std::make_shared<SceneObject>(r3, l3, "Light");
        scene->addObject(so3);

        std::shared_ptr<Rectangle> r4 = std::make_shared<Rectangle>(glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(-2.00f,0,0),glm::vec3(0,0,1.00f));
        std::shared_ptr<Lambertian> l4 = std::make_shared<Lambertian>(white);
        std::shared_ptr<SceneObject> so4 = std::make_shared<SceneObject>(r4, l4, "White Rectangle 1");
        scene->addObject(so4);

        std::shared_ptr<Rectangle> r5 = std::make_shared<Rectangle>(glm::vec3(1.00f,1.00f,0.00f),glm::vec3(0,0,1.00f),glm::vec3(-2.00f,0,0));
        std::shared_ptr<Lambertian> l5 = std::make_shared<Lambertian>(white);
        std::shared_ptr<SceneObject> so5 = std::make_shared<SceneObject>(r5, l5, "White Rectangle 2");
        scene->addObject(so5);

        std::shared_ptr<Rectangle> r6 = std::make_shared<Rectangle>(glm::vec3(1,-1,1),glm::vec3(-2,0,0),glm::vec3(0,2,0));
        std::shared_ptr<Lambertian> l6 = std::make_shared<Lambertian>(blue);
        std::shared_ptr<SceneObject> so6 = std::make_shared<SceneObject>(r6, l6, "Blue Rectangle");
        scene->addObject(so6);

//        std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(glm::vec3(-25.0f,20.0f,50.0f),3);//1.9999
//        std::shared_ptr<Lambertian> l7 = std::make_shared<Lambertian>(red);
//        std::shared_ptr<SceneObject> so7 = std::make_shared<SceneObject>(sphere,l7);
//        m_scene->addObject(so7);
    }

    static void makeGuiForSceneObject(const std::shared_ptr<SceneObject>& sceneObject)
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

        Camera camera = Camera(Renderer::getViewportWidth(), Renderer::getViewportHeight());
        m_scene.reset(new Scene(camera));

        createCornellBoxScene(m_scene);
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

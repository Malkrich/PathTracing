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
#include "Renderer/Camera.h"

namespace PathTracing
{
	Editor::Editor()
	{
		// has to be called first
		Renderer::init();

        m_image.reset(new Image32UI(Renderer::getViewportWidth(), Renderer::getViewportHeight()));

        m_scene.reset(new Scene());

        Camera cam = Camera();
        cam.resize(Renderer::getViewportWidth(), Renderer::getViewportHeight());
        m_scene->setCamera(cam);

        glm::vec3 red = glm::vec3(.65,.05,.05);
//        glm::vec3 green = glm::vec3(.12,.45,.15);
//        glm::vec3 light = glm::vec3(1,1,1);
//        glm::vec3 white = glm::vec3(.73,.73,.73);

//        Rectangle* r1 = new Rectangle(glm::vec3(555.0f,0.0f,0.0f),glm::vec3(0,555,0),glm::vec3(0,0,555));
//        Lambertian* l1 = new Lambertian(green);
//        SceneObject* so1 = new SceneObject(r1,l1);
//        m_scene->addObject(so1);

//        Rectangle* r2 = new Rectangle(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0,555,0),glm::vec3(0,0,555));
//        Lambertian* l2 = new Lambertian(red);
//        SceneObject* so2 = new SceneObject(r1,l1);
//        m_scene->addObject(so2);

//        Rectangle* r3 = new Rectangle(glm::vec3(343,554,332),glm::vec3(-130,0,0),glm::vec3(0,0,105));
//        Lambertian* l3 = new Lambertian(light);
//        SceneObject* so3 = new SceneObject(r1,l1);
//        m_scene->addObject(so3);

//        Rectangle* r4 = new Rectangle(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(555,0,0),glm::vec3(0,0,555));
//        Lambertian* l4 = new Lambertian(white);
//        SceneObject* so4 = new SceneObject(r1,l1);
//        m_scene->addObject(so4);

//        Rectangle* r5 = new Rectangle(glm::vec3(555,555,555),glm::vec3(-555,0,0),glm::vec3(0,555,0));
//        Lambertian* l5 = new Lambertian(white);
//        SceneObject* so5 = new SceneObject(r1,l1);
//        m_scene->addObject(so5);

//        Rectangle* r6 = new Rectangle(glm::vec3(0,0,555),glm::vec3(555,0,0),glm::vec3(0,555,0));
//        Lambertian* l6 = new Lambertian(white);
//        SceneObject* so6 = new SceneObject(r1,l1);
//        m_scene->addObject(so6);

        Sphere* sphere = new Sphere(glm::vec3(1.0f,-2.0,0.0f),0.5);
        Lambertian* l7 = new Lambertian(red);
        SceneObject* so7 = new SceneObject(sphere,l7);
        m_scene->addObject(so7);

//        Plane* plane = new Plane(glm::vec3(0.0f,-2.0f,0.0f) , glm::vec3(0.0f,-1.0f,0.0f));
//        Lambertian* l8 = new Lambertian(white);
//        SceneObject* so8 = new SceneObject(sphere,l7);
//        m_scene->addObject(so8);
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
		std::string timeStat = "Delta time : ";
		timeStat += std::to_string(m_deltaTime * 1000.0f) + " ms";
		float fps = 1 / m_deltaTime;
		std::string fpsStat = "Fps : ";
		fpsStat += std::to_string(fps);

        std::string infoDimension = "Dimension : ["
                + std::to_string(Renderer::getViewportWidth()) + ", "
                + std::to_string(Renderer::getViewportHeight()) + "]";

        ImGui::Begin("Info : ");
		ImGui::Text(timeStat.c_str());
		ImGui::Text(fpsStat.c_str());
        ImGui::Text("");
        ImGui::Text(infoDimension.c_str());
		ImGui::End();
	}

}

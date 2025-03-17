#include "Pch.h"

#include "Core/EntryPoint.h"
#include "Core/Application.h"

#include "PathTracingLayer.h"

namespace PathTracing
{

	class PathTracingApplication : public Application
	{
	public:
		PathTracingApplication(const std::string& appName)
			: Application(appName)
		{}
	};

}

PathTracing::Application* createApplication()
{
	PathTracing::Application* app = new PathTracing::PathTracingApplication("Path Tracing");

	app->pushLayer<PathTracing::PathTracingLayer>();

	return app;
}
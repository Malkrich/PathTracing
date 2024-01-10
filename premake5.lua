workspace "PathTracing"
    architecture "x86"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
	{
		"MultiProcessorCompile"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}"

group "Application"
    include "PathTracing"

group "Dependencies"
    include "PathTracing/lib/glfw"
    include "PathTracing/lib/glad"
    include "PathTracing/lib/imgui"
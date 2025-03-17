project "PathTracing"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-int/" .. outputDir .. "/%{prj.name}")

    includedirs
    {
        "src",
        "lib/GLFW/glfw-3.3.8/include",
        "lib/glad/include",
        "lib/imgui",
        "lib/glm"
    }

    files
    {
        "src/**.h",
        "src/**.cpp",
        "lib/glm/**.hpp",
        "lib/glm/**.inl"
    }

    pchheader "Pch.h"
    pchsource "src/Pch.cpp"

    links
    {
        "GLFW",
        "glad",
        "imgui"
    }

    filter "configurations:Debug"
        defines
        {
            "PT_DEBUG",
            "PT_GRAPHIC_DEBUG"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines
        {
            "PT_RELEASE"
        }
        runtime "Release"
        symbols "On"
        optimize "On"
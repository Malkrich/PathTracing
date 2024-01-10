project "PathTracing"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    systemversion "latest"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("bin-int/" .. outputDir .. "/%{prj.name}")

    debugdir "../"

    includedirs
    {
        "src",
        "lib/glfw/include",
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

    links
    {
        "GLFW",
        "glad",
        "imgui"
    }

    filter "configurations:Debug"
        --defines "PT_DEBUG"
        runtime "Debug"

    filter "configurations:Release"
        --defines "PT_RELEASE"
        runtime "Release"
        optimize "on"
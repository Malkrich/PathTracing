cmake_minimum_required(VERSION 3.22)

project(PathTracing LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    PathTracing/src/
    PathTracing/lib/glad/include/
    PathTracing/lib/glm/
    PathTracing/lib/imgui/
)

file(GLOB_RECURSE LIB_FILES     "PathTracing/lib/glad/*.c"
#--------------------------------- IMGUI ---------------------#
                                "PathTracing/lib/imgui/imconfig.h"
                                "PathTracing/lib/imgui/imgui.cpp"
                                "PathTracing/lib/imgui/imgui.h"
                                "PathTracing/lib/imgui/imgui_demo.cpp"
                                "PathTracing/lib/imgui/imgui_draw.cpp"
                                "PathTracing/lib/imgui/imgui_internal.h"
                                "PathTracing/lib/imgui/imgui_tables.cpp"
                                "PathTracing/lib/imgui/imgui_widgets.cpp"
                                "PathTracing/lib/imgui/imstb_rectpack.h"
                                "PathTracing/lib/imgui/imstb_textedit.h"
                                "PathTracing/lib/imgui/imstb_truetype.h"

                                "PathTracing/lib/imgui/backends/imgui_impl_opengl3.cpp"
                                "PathTracing/lib/imgui/backends/imgui_impl_opengl3.h"
                                "PathTracing/lib/imgui/backends/imgui_impl_glfw.cpp"
                                "PathTracing/lib/imgui/backends/imgui_impl_glfw.h"
#-------------------------------------------------------------#
)
file(GLOB_RECURSE SOURCE_FILES  "PathTracing/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES  "PathTracing/src/*.h")

source_group("header"   FILES ${HEADER_FILES})
source_group("sources"  FILES ${SOURCE_FILES})
source_group("lib"      FILES ${LIB_FILES})

add_definitions(-DGLFW_INCLUDE_NONE)
add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES} ${HEADER_FILES}
    ${LIB_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    glfw
    OpenGL::GL
)

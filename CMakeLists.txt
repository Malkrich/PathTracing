cmake_minimum_required(VERSION 3.22)

project(PathTracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
if(NOT ${OPENGL_FOUND})
  message("OpenGL not found")
endif()

find_package(GLEW)
if(NOT ${GLEW_FOUND} OR APPLE)

  message(WARNING "Glew not found, manual compilation of glew added to the project")

  # option(glew-cmake_BUILD_SHARED "Build the shared glew library" OFF)
  # option(ONLY_LIBS "Do not build executables" ON)

  # add_subdirectory(PathTracing/lib/GLEW)
  # include_directories(${CMAKE_SOURCE_DIR}/PathTracing/lib/GLEW/include)
  # set(USED_GLEW_LIBRARY libglew_static)
else()
  include_directories(${GLEW_INCLUDE_DIRS})
  set(USED_GLEW_LIBRARY ${GLEW_LIBRARIES})
endif()

include_directories(${CMAKE_SOURCE_DIR}/extern)

file(GLOB source_files "PathTracing/src/*.cpp")
file(GLOB header_files "PathTracing/src/*.h")

message("Source files")
foreach(line IN LISTS source_files)
  message("${line}")
endforeach()

message("Header files")
foreach(line IN LISTS header_files)
  message("${line}")
endforeach()

if (WIN32)
  set(LINK_FLAGS )
elseif (APPLE)
  set(LINK_FLAGS )
elseif (UNIX)
  set(LINK_FLAGS )
  add_definitions(-g -Wall -Wextra -Wno-comment -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable)
endif ()

add_executable(PathTracing ${source_files} ${header_files} ${shader_files})
target_link_libraries(PathTracing ${USED_GLEW_LIBRARY} ${USED_GLUT_LIBRARY} ${OPENGL_LIBRARIES} ${LINK_FLAGS})
set_target_properties(PathTracing PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT PathTracing)

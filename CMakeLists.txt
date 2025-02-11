CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(ogl LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_BUILD_TYPE EQUAL "Debug")
    add_compile_definitions(_DEBUG)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -I${CMAKE_SOURCE_DIR}/libs/include")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_definitions(_SOLUTIONDIR="${CMAKE_SOURCE_DIR}")

find_package(imgui)
find_package(glm)
add_subdirectory(libs/glad)
set(GLFWPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # disable building GLFWPP examples
SET(IMGUI_BUILD_GLFW_BINDING ON)
add_subdirectory(libs/glfwpp)

set(SOURCES
    ./src/Main.cpp
    ./src/VertexArray.cpp
    ./src/VertexBuffer.cpp
    ./src/Window.cpp
    ./src/Utility.cpp
    ./src/Shader.cpp
    ./src/Renderer.cpp
    ./src/Texture.cpp
    ./test/TestClearColor.cpp
    ./test/TestTexture.cpp
    ./test/TestPerspective.cpp
    ./test/TestCollisions.cpp
    ./libs/imgui/imgui_impl_glfw.cpp
    ./libs/imgui/imgui_impl_opengl3.cpp
    )

add_executable(ogl ${SOURCES})
target_compile_features(ogl PRIVATE cxx_std_20)
target_include_directories(ogl PUBLIC ${CMAKE_SOURCE_DIR}/libs/imgui ${CMAKE_SOURCE_DIR}/libs/glad/include ${CMAKE_SOURCE_DIR}/libs/glfwpp/include ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/test)
target_link_libraries(ogl PRIVATE GLFWPP ${glfw3_LIBRARIES} imgui ${glm_LIBRARIES} glad)

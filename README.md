# OpenGL Engine

Repository containing the result of [The Cherno's OpenGL youtube series](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2) on linux.

# Building

- Install the building dependencies `imgui`, `clang`, `libc++`/`libcxx`, `python-glad`, `stb`, `glm`, `cmake` and `ninja`.

- Create the folders `libs/glad` and `libs/imgui`.

- Inside `libs` clone the [glfwpp](https://github.com/janekb04/glfwpp) repository.

- Inside `libs/glad` run the [glad](https://github.com/Dav1dde/glad) generator and create a file named `CMakeLists.txt` with the following contents:

```cmake
cmake_minimum_required(VERSION 3.16...3.27)
project(glad LANGUAGES C)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

```

- Inside `libs/imgui` download the following files from the [imgui repository](https://github.com/ocornut/imgui):

```
.
└── backends/
    ├── imgui_impl_glfw.h
    ├── imgui_impl_glfw.cpp
    ├── imgui_impl_opengl3.h
    ├── imgui_impl_opengl3.cpp
    └── imgui_impl_opengl3_loader.h
```

- Check the libs folder looks like this:
```
.
└── libs/
    ├── glfwpp/
    │   └── ...
    ├── glad/
    │   ├── glad.c
    │   ├── glad.h
    │   └── CMakeLists.txt
    └── imgui/
        ├── imgui_impl_glfw.h
        ├── imgui_impl_glfw.cpp
        ├── imgui_impl_opengl3.h
        ├── imgui_impl_opengl3.cpp
        └── imgui_impl_opengl3_loader.h
```

- Back in the root of the project run generate cmake files
`CC=clang CXX=clang++ cmake -B build -G Ninja` or `CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=RELEASE -B build -G Ninja` for a release build.

- Build the project
`cmake --build build`

- If building in release mode, move the `build/ogl` binary to the root of the project.

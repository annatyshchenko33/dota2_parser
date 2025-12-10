cmake_minimum_required(VERSION 3.20)
project(Dota2Parser)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/Window.cpp
    include/Window.h
    src/BaseParser.cpp
    include/BaseParser.h
    src/JsonParser.cpp
    include/JsonParser.h
    src/Fetcher.cpp
    include/Fetcher.h
    src/Image.cpp
    include/Image.h
)

# -------------------------------
# RapidJSON (header-only)
# -------------------------------
add_library(rapidjson INTERFACE)
target_include_directories(rapidjson INTERFACE 
    ${CMAKE_SOURCE_DIR}/external/rapidjson/include
)



# -------------------------------
# FetchContent
# -------------------------------
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.10
)
FetchContent_MakeAvailable(glfw)

# httplib
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG v0.15.3
)
FetchContent_MakeAvailable(httplib)

# -------------------------------
# ImGui
# -------------------------------
add_library(imgui
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    external/imgui
    external/imgui/backends
    ${glfw_SOURCE_DIR}/include
    include
)

add_library(curl STATIC IMPORTED)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/Lenovo/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# -------------------------------
# OpenGL
# -------------------------------
find_package(OpenGL REQUIRED)

# -------------------------------
# Executable
# -------------------------------
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/external/stb
)

# -------------------------------
# Link libraries
# -------------------------------
target_link_libraries(${PROJECT_NAME}
    imgui
    glfw
    opengl32         # ← Windows OpenGL
    rapidjson
    httplib::httplib
)

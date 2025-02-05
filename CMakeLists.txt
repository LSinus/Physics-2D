cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

project(Physics-2D)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
find_package(OpenGL REQUIRED)

add_executable(Physics-2D main.cpp vec2.h
        external/imgui/imconfig.h
        external/imgui/imgui.cpp
        external/imgui/imgui.h
        external/imgui/imgui_demo.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_internal.h
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imstb_rectpack.h
        external/imgui/imstb_textedit.h
        external/imgui/imstb_truetype.h
        external/imgui-sfml/imconfig-SFML.h
        external/imgui-sfml/imgui-SFML.cpp
        physicsObject.h
        physicsWorld.h
        physicsWorld.cpp
        Link.h
        utils.h)

target_include_directories(Physics-2D PRIVATE
        external/imgui
        external/imgui-sfml
)


target_link_libraries(Physics-2D PRIVATE SFML::Graphics SFML::Window SFML::System OpenGL::GL)


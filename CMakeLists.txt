cmake_minimum_required(VERSION 3.5)
project(SunflowerSpaniel)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SunflowerSpaniel_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
INCLUDE(FindSDL2 REQUIRED)
INCLUDE(FindOpenGL REQUIRED)
INCLUDE(FindGLEW REQUIRED)
INCLUDE(FindBox2D REQUIRED)
INCLUDE(FindLibNoise REQUIRED)

include_directories(${SunflowerSpaniel_SOURCE_DIR}/include
        ${BOX2D_INCLUDE_DIR} ${SDL2_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} {LIBNOISE_INCLUDE_DIR})

set(SOURCE_FILES
        src/App.cpp
        src/App.h
        src/GameplayScreen.cpp
        src/GameplayScreen.h
        src/main.cpp
        src/Box.cpp
        src/Box.h
        src/Player.cpp
        src/Player.h
        src/Circle.cpp
        src/Circle.h
        include/ImGUI/imgui.cpp
        include/ImGUI/imgui.h
        include/ImGUI/imgui_impl_sdl.cpp
        include/ImGUI/imgui_impl_sdl.h
        include/ImGUI/imgui_draw.cpp
        include/ImGUI/imgui_internal.h
        src/Map.cpp src/Map.h)

add_executable(SunflowerSpaniel ${SOURCE_FILES})
include(FindPkgConfig)
find_package(libFalconLatinum REQUIRED)
include_directories(${FALCONLATINUM_INCLUDE_DIR})
target_link_libraries(SunflowerSpaniel ${SDL2_LIBRARY} ${OPENGL_LIBRARIES}
        ${FALCONLATINUM_LIBRARY} ${GLEW_LIBRARIES} ${BOX2D_LIBRARY} ${LIBNOISE_LIBRARY})
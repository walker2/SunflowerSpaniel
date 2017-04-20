cmake_minimum_required(VERSION 3.5)
project(SunflowerSpaniel)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SunflowerSpaniel_SOURCE_DIR}/cmake")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -g3")
INCLUDE(FindSDL2 REQUIRED)
INCLUDE(FindOpenGL REQUIRED)
INCLUDE(FindGLEW REQUIRED)
INCLUDE(FindBox2D REQUIRED)
INCLUDE(FindSDL2_ttf REQUIRED)
INCLUDE(FindLibNoise REQUIRED)

include_directories(${SunflowerSpaniel_SOURCE_DIR}/include
        ${BOX2D_INCLUDE_DIR} ${SDL2_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${LIBNOISE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIRS})

set(SOURCE_FILES
        src/Application/App.cpp
        src/Application/App.h
        src/Screens/GameplayScreen.cpp
        src/Screens/GameplayScreen.h
        src/main.cpp
        include/ImGUI/imgui.cpp
        include/ImGUI/imgui.h
        include/ImGUI/imgui_impl_sdl.cpp
        include/ImGUI/imgui_impl_sdl.h
        include/ImGUI/imgui_draw.cpp
        include/ImGUI/imgui_internal.h
        include/ImGUI/imgui_demo.cpp
        include/TinyXML2/tinyxml2.cpp
        include/TinyXML2/tinyxml2.h
        src/Map/Map.cpp src/Map/Map.h
        src/Components/Component.h
        src/ObjectFactory/GameObject.cpp
        src/ObjectFactory/GameObject.h
        src/Components/BodyComponent.cpp
        src/Components/BodyComponent.h
        src/Components/SpriteComponent.cpp
        src/Components/SpriteComponent.h
        src/Components/CollisionComponent.cpp
        src/Components/CollisionComponent.h
        src/Components/PlayerInputComponent.cpp
        src/Components/PlayerInputComponent.h src/ObjectFactory/ObjectFactory.cpp src/ObjectFactory/ObjectFactory.h src/Components/AnimationComponent.cpp src/Components/AnimationComponent.h src/Screens/MainMenuScreen.cpp src/Screens/MainMenuScreen.h src/Screens/ScreenIndices.h src/Components/DirectionalAnimationComponent.cpp src/Components/DirectionalAnimationComponent.h src/Components/SensorComponent.cpp src/Components/SensorComponent.h src/Messaging/ContactListener.h src/Components/InteractiveComponent.cpp src/Components/InteractiveComponent.h src/Messaging/Messages.h src/Components/SpawnObjectComponent.cpp src/Components/SpawnObjectComponent.h src/Messaging/Telegram.h src/Messaging/MessageManager.cpp src/Messaging/MessageManager.h src/FSM/State.h src/FSM/StateManager.h src/Components/DogAIComponent.cpp src/Components/DogAIComponent.h src/States/DogOwnedStates.cpp src/States/DogOwnedStates.h)

add_executable(SunflowerSpaniel ${SOURCE_FILES})
include(FindPkgConfig)
find_package(libFalconLatinum REQUIRED)
include_directories(${FALCONLATINUM_INCLUDE_DIR})
target_link_libraries(SunflowerSpaniel ${SDL2_LIBRARY} ${OPENGL_LIBRARIES}
        ${FALCONLATINUM_LIBRARY} ${GLEW_LIBRARIES} ${BOX2D_LIBRARY} libnoise.so ${SDL2_TTF_LIBRARIES})

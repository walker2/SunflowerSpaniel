#ifndef SUNFLOWERSPANIEL_GAMEPLAYSCREEN_H
#define SUNFLOWERSPANIEL_GAMEPLAYSCREEN_H


#include <vector>
#include <bits/unique_ptr.h>
#include <Box2D/Box2D.h>

#include "Box.h"
#include "Player.h"
#include "Map.h"

#include "Falcon/GameIntefaces/IGameScreen.h"
#include "Falcon/GLSL/ShaderProgram.h"
#include "Falcon/2D/Camera/Camera2D.h"
#include "Falcon/2D/SpriteBatch/SpriteBatch.h"
#include "Falcon/2D/GLTexture.h"
#include "Falcon/Window/Window.h"
#include "Falcon/2D/DebugRenderer/DebugRenderer.h"
#include "Falcon/GUI/GUI.h"
#include "Falcon/2D/Lights/BasicLight.h"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"



class GameplayScreen : public Falcon::IGameScreen
{
public:
    GameplayScreen(Falcon::Window* window);
    ~GameplayScreen() {};
    int getNextScreenIndex() const override;

    int getPrevScreenIndex() const override;

    void create() override;

    void destroy() override;

    void onEntry() override;

    void onExit() override;

    void update() override;

    void draw() override;

private:
    void checkInput();

    bool m_renderDebug = false;
    float mouse_color[3];

    Falcon::ShaderProgram m_shaderProgram;
    Falcon::ShaderProgram m_lightProgram;
    Falcon::Camera2D m_camera;
    Falcon::SpriteBatch m_spriteBatch;
    Falcon::GLTexture m_texture;
    Falcon::Window* m_window;
    Falcon::DebugRenderer m_debugRender;

    Falcon::BasicLight playerLight;
    Falcon::BasicLight mouseLight;

    Player m_player;
    Map m_map;
    std::vector<Box> m_boxes;
    std::unique_ptr<b2World> m_world;


};


#endif

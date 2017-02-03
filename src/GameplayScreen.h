#ifndef SUNFLOWERSPANIEL_GAMEPLAYSCREEN_H
#define SUNFLOWERSPANIEL_GAMEPLAYSCREEN_H


#include <vector>
#include <bits/unique_ptr.h>
#include <Box2D/Box2D.h>

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
#include "ObjectFactory.h"


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

    void update(float deltaTime) override;

    void draw(float deltaTime) override;

private:
    void checkInput();
    std::shared_ptr<GameObject> createCircle(b2World *world, const glm::vec2 position, const glm::vec2 dimensions,
                                             bool fixedRotation, b2BodyType bodyType);
    std::shared_ptr<GameObject> createPlayer(b2World *world,
                                             const glm::vec2 collisionPosition,
                                             const glm::vec2 spritePosition,
                                             const glm::vec2 collisionDimensions,
                                             const glm::vec2 spriteDimensions,
                                             const std::string &texturePath,
                                             Falcon::Color color, int spriteID);

    void compileShader(Falcon::ShaderProgram& shaderProgram, const std::string& vertPath, const std::string& fragPath);

    bool m_renderDebug = false;
    float mouse_color[3];
    float m_time = 0.0f;
    int m_darker = 1;

    Falcon::ShaderProgram m_textureProgram;
    Falcon::ShaderProgram m_lightProgram;
    Falcon::Camera2D m_camera;
    Falcon::SpriteBatch m_spriteBatch;
    Falcon::SpriteBatch m_lightSpriteBatch;
    Falcon::Window* m_window;
    Falcon::DebugRenderer m_debugRender;

    Falcon::BasicLight playerLight;
    Falcon::BasicLight mouseLight;
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;

    ObjectFactory m_objectFactory;
    Player m_player;
    Map m_map;
    std::unique_ptr<b2World> m_world;


};


#endif

#ifndef SUNFLOWERSPANIEL_GAMEPLAYSCREEN_H
#define SUNFLOWERSPANIEL_GAMEPLAYSCREEN_H


#include <vector>
#include <bits/unique_ptr.h>
#include <Box2D/Box2D.h>
#include "../Map/Map.h"

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
#include "../ObjectFactory/ObjectFactory.h"
#include "../GUI/DebugGUI.h"
#include "../GUI/InventoryGUI.h"

/**
 * GameScreen that implements GameplayScreen in Application
 */
class GameplayScreen : public Falcon::IGameScreen
{
public:
    /**
    * Constructor, sets m_screenIndex and m_window
    * @param window a pointer to a window the MainMenu should be displayed
    */
    GameplayScreen(Falcon::Window *window);

    ~GameplayScreen()
    {}

    /**
    * Gets a next screen index
    * @return next screen index
    */
    int getNextScreenIndex() const override;

    /**
     * Gets a previous screen index
     * @return previous screen index
     */
    int getPrevScreenIndex() const override;

    /**
     * Called once, when the Screen are created
     */
    void create() override;

    /**
     * Called once, when the Screen are destroyed
     */
    void destroy() override;

    /**
     * Called every time we switch to the this Screen
     */
    void onEntry() override;

    /**
    * Called every time we switch from this screen to another
    */
    void onExit() override;

    /**
     * Update function that called every frame in Main Cycle
     * @param deltaTime time that have passed since the last frame
     */
    void update(float deltaTime) override;

    /**
     * Draw function that called every frame in Main Cycle
     * @param deltaTime time that have passed since the last frame
     */
    void draw(float deltaTime) override;

private:
    /**
     * Function that pulls SDL_Events from m_game
     */
    void checkInput();

    /**
    * Function that compiles vertex and fragment shader from their paths
    * @param shaderProgram program we should compile with
    * @param vertPath path to the vertex shader
    * @param fragPath path to the fragment shader
    */
    void compileShader(Falcon::ShaderProgram &shaderProgram, const std::string &vertPath, const std::string &fragPath);

    bool m_renderDebug = false;
    float mouse_color[3];
    float m_time = 0.0f;
    int m_darker = 1;
    bool m_showInventory = false;

    Falcon::ShaderProgram m_textureProgram; ///< Shader program for texture shader compiling
    Falcon::ShaderProgram m_lightProgram;   ///< Shader program for light shader compiling
    Falcon::Camera2D m_camera;              ///< Camera for scene drawing
    Falcon::SpriteBatch m_spriteBatch;      ///< A batch we draw to all gameObjects
    Falcon::SpriteBatch m_lightSpriteBatch; ///< A batch we draw to all lights
    Falcon::Window *m_window;               ///< A window we display to
    Falcon::DebugRenderer m_debugRender;    ///< Special render type for Debug purposes
    Falcon::BasicLight playerLight;
    Falcon::BasicLight mouseLight;

    std::shared_ptr<GameObject> m_currentPlayer;   ///< Player gameObject handle
    std::shared_ptr<GameObject> m_dogPlayer;
    std::shared_ptr<GameObject> m_humanPlayer;
    std::unique_ptr<b2World> m_world;       ///< World for physics simulation

    Map m_map;                              ///< Map object that draws all background sprites
    DebugGUI m_debugGUI;
    InventoryGUI m_inventoryGUI;
};


#endif

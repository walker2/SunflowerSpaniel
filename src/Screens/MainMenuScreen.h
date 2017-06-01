#ifndef SUNFLOWERSPANIEL_MAINMENUSCREEN_H
#define SUNFLOWERSPANIEL_MAINMENUSCREEN_H


#include <Falcon/GameIntefaces/IGameScreen.h>
#include <Falcon/Window/Window.h>
#include <Falcon/GLSL/ShaderProgram.h>
#include <Falcon/2D/Camera/Camera2D.h>
#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "../ObjectFactory/GameObject.h"

/**
 * GameScreen that implements MainMenu in Application
 */
class MainMenuScreen : public Falcon::IGameScreen
{
public:
    /**
     * Constructor, sets m_screenIndex and m_window
     * @param window a pointer to a window the MainMenu should be displayed
     */
    MainMenuScreen(Falcon::Window *window);

    ~MainMenuScreen()
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
    void draw(float deltaTime) override;;

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


    Falcon::ShaderProgram m_textureProgram; ///< Shader program for texture shader compiling
    Falcon::Camera2D m_camera;              ///< Camera for scene drawing
    Falcon::SpriteBatch m_spriteBatch;      ///< A batch we draw to
    Falcon::Window *m_window;               ///< A window we display to
    std::vector<std::shared_ptr<GameObject>> m_gameObjects; ///< Vector of all gameObjects on scene

    std::unique_ptr<b2World> m_world;       ///< World for physics simulation

};


#endif

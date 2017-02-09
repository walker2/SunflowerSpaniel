#ifndef SUNFLOWERSPANIEL_MAINMENUSCREEN_H
#define SUNFLOWERSPANIEL_MAINMENUSCREEN_H


#include <Falcon/GameIntefaces/IGameScreen.h>
#include <Falcon/Window/Window.h>
#include <Falcon/GLSL/ShaderProgram.h>
#include <Falcon/2D/Camera/Camera2D.h>
#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "GameObject.h"

class MainMenuScreen : public Falcon::IGameScreen
{
public:
    MainMenuScreen(Falcon::Window* window);
    ~MainMenuScreen() {}

    int getNextScreenIndex() const override;

    int getPrevScreenIndex() const override;

    void create() override;

    void destroy() override;

    void onEntry() override;

    void onExit() override;

    void update(float deltaTime) override;

    void draw(float deltaTime) override;;

private:
    void checkInput();
    void compileShader(Falcon::ShaderProgram& shaderProgram, const std::string& vertPath, const std::string& fragPath);


    Falcon::ShaderProgram m_textureProgram;
    Falcon::Camera2D m_camera;
    Falcon::SpriteBatch m_spriteBatch;
    Falcon::Window* m_window;
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;

    std::unique_ptr<b2World> m_world;

};


#endif

#ifndef FALCONLATINUM_GAME_H
#define FALCONLATINUM_GAME_H

#include <vector>
#include "SDL2/SDL.h"
#include "GL/glew.h"
#include "../States/StateManager.h"
#include "../2D/Sprite.h"
#include "../GLSL/ShaderProgram.h"
#include "../2D/GLTexture.h"
#include "../Window/Window.h"
#include "../2D/Camera/Camera2D.h"
#include "Falcon.h"
#include "../2D/SpriteBatch/SpriteBatch.h"
#include "../InputOutput/InputManager.h"
#include "../Timing/Timing.h"
#include "../Object/Projectile.h"


class Game
{
public:

    Game() : m_screenWidth(1024), m_screenHeight(720), m_currentState(Falcon::StateType::PLAY), m_time(0) { m_camera.init(m_screenWidth, m_screenHeight); };
    ~Game() {};
    void run();

private:
    void initSystems();
    void initShaders();
    void processInput();
    void gameLoop();
    void draw();

private:
    int m_screenWidth;
    int m_screenHeight;

    Falcon::Window m_window;
    Falcon::StateType m_currentState;
    Falcon::ShaderProgram m_shaderProgram;
    Falcon::Camera2D m_camera;
    Falcon::SpriteBatch m_spriteBatch;
    Falcon::InputManager m_inputManager;
    Falcon::FPSLimiter m_FPSLimiter;

    std::vector<Falcon::Projectile> m_projectiles;

    float m_FPS;
    float m_time;
};

#endif
#include "GameplayScreen.h"
#include "Falcon/GameIntefaces/IMainGame.h"
#include "ScreenIndices.h"

#include "../Messaging/ContactListener.h"

ContactListener listener;

GameplayScreen::GameplayScreen(Falcon::Window *window)
        : m_window(window)
{
    m_screenIndex = SCREEN_INDEX_GAMEPLAY;
}

int GameplayScreen::getNextScreenIndex() const
{
    return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPrevScreenIndex() const
{
    return SCREEN_INDEX_MAINMENU;
}

void GameplayScreen::create()
{
    ImGui_ImplSdl_Init(m_window->getSDLWindow());

    m_debugRender.init();

    //Init spritebatch
    m_spriteBatch.init();
    m_lightSpriteBatch.init();

    // Compile texture and light shader
    compileShader(m_textureProgram, "include/Falcon/Shaders/textureShading.vert",
                  "include/Falcon/Shaders/textureShading.frag");
    compileShader(m_lightProgram, "include/Falcon/Shaders/lightShading.vert",
                  "include/Falcon/Shaders/lightShading.frag");

    // Init camera
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
    m_camera.setScale(16.0f);

    playerLight.color = Falcon::Color(62, 96, 111, 0);
    playerLight.size = 100.0f;

    mouseLight.color = Falcon::Color(0, 0, 0, 128);
    mouseLight.size = 15.0f;
}

void GameplayScreen::destroy()
{
    m_debugRender.dispose();
}

void GameplayScreen::onEntry()
{
    b2Vec2 gravity(0.0f, 0.0f);
    m_world = std::make_unique<b2World>(gravity);
    ObjectFactory::instance().setWorld(m_world.get());
    m_world->SetContactListener(&listener);

    m_dogPlayer = ObjectFactory::instance().createObject("media/Objects/DogPlayer.xml");
    m_humanPlayer = ObjectFactory::instance().createObject("media/Objects/HumanPlayer.xml");
    m_dogPlayer->setLayer(1);
    m_humanPlayer->setLayer(1);

    ObjectFactory::instance().addObject(m_dogPlayer);
    ObjectFactory::instance().addObject(m_humanPlayer);
    ObjectFactory::instance().setDogPlayerID(m_dogPlayer->getID());
    ObjectFactory::instance().setHumanPlayerID(m_humanPlayer->getID());

    m_currentPlayer = m_humanPlayer;
    ObjectFactory::instance().setCurrentPlayerID(m_currentPlayer->getID());


    m_map.init(m_world.get(), 200, 200, "media/Textures/terrain.png", 32);
    m_map.generateMap();
}

void GameplayScreen::onExit()
{
    ObjectFactory::instance().dispose();
    m_map.dispose();
}

void GameplayScreen::update(float deltaTime)
{
    checkInput();

    ObjectFactory::instance().updateGameObjects(deltaTime);
    // TODO: MAYBE A CAMERA FOLLOW COMPONENT?

    auto playerPos = m_currentPlayer->getComponent<BodyComponent>()->getPosition();

    glm::vec2 newCamPos = playerPos;
    if (playerPos.x <= 43 || playerPos.x >= 556)
    {
        newCamPos.x = m_camera.getPosition().x;
    }
    if (playerPos.y <= 26 || playerPos.y >= 574)
    {
        newCamPos.y = m_camera.getPosition().y;
    }

    m_camera.setPosition(newCamPos);
    m_camera.update();

    // TODO: MAKE A LIGHT COMPONENT
    playerLight.position = m_currentPlayer->getComponent<BodyComponent>()->getPosition();
    glm::vec2 mousePos = m_camera.screenToWorld(Falcon::InputManager::instance().getMouseCoords());
    mouseLight.position = mousePos;



    // Update the physics simulation
    m_world->Step(1.0f / 60.0f, 3, 2);

    if (m_time < 0.0f)
    {
        m_darker = 1;
    } else if (m_time > 0.7f)
    {
        m_darker = -1;
    }

    m_time += m_darker * 0.001f * deltaTime;
    playerLight.color.a = static_cast<GLubyte>(m_time * (200 / 0.7));

    if (Falcon::InputManager::instance().isKeyPressed(SDLK_ESCAPE))
    {
        m_currentState = Falcon::ScreenState::CHANGE_PREV;
    }

    //TODO: FOR TESTING ONLY, SHOULD BE REPLACED IN INPUT COMPONENT CODE
    if (ImGui::IsKeyPressed(SDLK_TAB, false) && m_currentPlayer->getComponent<PlayerInputComponent>()->isEnabled())
    {
        if (m_currentPlayer == m_humanPlayer)
        {
            m_humanPlayer->getComponent<PlayerInputComponent>()->enable(false);
            m_dogPlayer->getComponent<PlayerInputComponent>()->enable(true);
            m_humanPlayer->getComponent<SensorComponent>()->enable(false);
            m_dogPlayer->getComponent<SensorComponent>()->enable(true);
            m_currentPlayer = m_dogPlayer;
        } else if (m_currentPlayer == m_dogPlayer)
        {
            m_humanPlayer->getComponent<PlayerInputComponent>()->enable(true);
            m_dogPlayer->getComponent<PlayerInputComponent>()->enable(false);
            m_humanPlayer->getComponent<SensorComponent>()->enable(true);
            m_dogPlayer->getComponent<SensorComponent>()->enable(false);
            m_currentPlayer = m_humanPlayer;
        }

        ObjectFactory::instance().setCurrentPlayerID(m_currentPlayer->getID());
        m_showInventory = false;
    }

    if (ImGui::IsKeyPressed(SDLK_i, false) && m_currentPlayer->getComponent<PlayerInputComponent>()->isEnabled())
    {
        m_showInventory = !m_showInventory;
    }

    ObjectFactory::instance().deleteGameObjects();
}

void GameplayScreen::draw(float deltaTime)
{
    ImGui_ImplSdl_NewFrame(m_window->getSDLWindow());

    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    m_textureProgram.use();

    // Upload texture uniform
    GLint textureUniform = m_textureProgram.getUniformLocation("sampler");
    glUniform1i(textureUniform, 0);

    // Upload color uniform
    glm::vec4 color(1.0 - m_time, 1.0 - m_time, 1.0 - m_time / 2, 1.0);
    GLint colorUniform = m_textureProgram.getUniformLocation("color");
    glUniform4fv(colorUniform, 1, &color[0]);

    // Camera matrix
    glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
    GLint pUniform = m_textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    if (m_map.isGenerated())
    {
        m_map.drawBackground();
    }

    m_textureProgram.unuse();

    m_lightProgram.use();
    // Additive blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    pUniform = m_textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    m_spriteBatch.begin();
    playerLight.draw(m_spriteBatch);
    mouseLight.draw(m_spriteBatch);
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();

    m_lightProgram.unuse();

    // Reset to regular alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_textureProgram.use();

    m_spriteBatch.begin();
    ObjectFactory::instance().drawGameObjects(m_spriteBatch, deltaTime, m_camera, m_debugRender, m_renderDebug);
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();

    if (m_map.isGenerated())
    {
        m_map.drawForeground();
    }
    m_textureProgram.unuse();

    m_debugRender.end();
    m_debugRender.render(projectionMatrix, 2.0f);

    m_debugGUI.begin();
    m_debugGUI.draw(m_renderDebug, mouseLight, playerLight, m_camera, m_currentPlayer, m_time);
    m_debugGUI.end();

    if (m_showInventory)
    {
        m_inventoryGUI.begin();
        m_inventoryGUI.draw(m_currentPlayer);
        m_debugGUI.end();
    }
    ImGui::Render();
}

void GameplayScreen::checkInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        m_game->onSDLEvent(e);
        ImGui_ImplSdl_ProcessEvent(&e);
    }
}

void GameplayScreen::compileShader(Falcon::ShaderProgram &shaderProgram, const std::string &vertPath,
                                   const std::string &fragPath)
{
    shaderProgram.compileShaders(vertPath, fragPath);
    shaderProgram.addAttribute("vertexPosition");
    shaderProgram.addAttribute("vertexColor");
    shaderProgram.addAttribute("vertexUV");
    shaderProgram.linkShaders();
}









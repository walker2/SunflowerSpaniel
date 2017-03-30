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

    m_player = ObjectFactory::instance().createObject("media/Objects/Player.xml");
    m_player->setLayer(1);
    ObjectFactory::instance().addObject(m_player);

    m_map.init(m_world.get(), 200, 200, "media/Textures/terrain.png", 32);
    m_map.generateMap();
}

void GameplayScreen::onExit()
{
    //m_gameObjects->clear();
    m_map.dispose();
}

void GameplayScreen::update(float deltaTime)
{
    checkInput();

    ObjectFactory::instance().updateGameObjects(deltaTime);
    // TODO: MAYBE A CAMERA FOLLOW COMPONENT?

    auto playerPos = m_player->getComponent<BodyComponent>()->getPosition();

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
    playerLight.position = m_player->getComponent<BodyComponent>()->getPosition();
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


    bool open = true;
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    if (!ImGui::Begin("Fixed Overlay", &open, ImVec2(0, 0), 0.3f,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                      ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::End();
        return;
    }


    if (ImGui::Button("Debug mode"))
    {
        m_renderDebug = !m_renderDebug;
    }
    ImGui::SameLine();
    if (ImGui::Button("Random mouse color"))
    {
        std::mt19937 rng(time(0));
        std::uniform_int_distribution<int> color(0, 255);
        mouseLight.color.r = static_cast<GLubyte>(color(rng));
        mouseLight.color.g = static_cast<GLubyte>(color(rng));
        mouseLight.color.b = static_cast<GLubyte>(color(rng));
    }
    ImGui::Separator();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::Text("Mouse position (%.2f, %.2f)",
                m_camera.screenToWorld(Falcon::InputManager::instance().getMouseCoords()).x,
                m_camera.screenToWorld(Falcon::InputManager::instance().getMouseCoords()).y);
    ImGui::Text("Player position (%.2f, %.2f)", m_player->getComponent<BodyComponent>()->getPosition().x,
                m_player->getComponent<BodyComponent>()->getPosition().y);
    ImGui::Text("Time %.5f", m_time);
    ImGui::Text("Player light alpha %i", playerLight.color.a);
    ImGui::Text("Number of objects on 0 layer %li", ObjectFactory::instance().getNumberOfGameObjectsOnLayer(0));
    ImGui::Text("Number of objects on 1 layer %li", ObjectFactory::instance().getNumberOfGameObjectsOnLayer(1));
    ImGui::Text("Number of objects on 2 layer %li", ObjectFactory::instance().getNumberOfGameObjectsOnLayer(2));
    ImGui::Text("Number of objects on 3 layer %li", ObjectFactory::instance().getNumberOfGameObjectsOnLayer(3));
    ImGui::Text("RAM usage by app %i kbytes", getRamUsage());
    ImGui::End();
    ImGui::Render();

}

int parseLine(char *line)
{
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = (int) strlen(line);
    const char *p = line;
    while (*p < '0' || *p > '9') p++;
    line[i - 3] = '\0';
    i = atoi(p);
    return i;
}

int GameplayScreen::getRamUsage()
{ //Note: this value is in KB!
    FILE *file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL)
    {
        if (strncmp(line, "VmRSS:", 6) == 0)
        {
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
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









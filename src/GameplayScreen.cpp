#include <iostream>
#include "GameplayScreen.h"
#include "Falcon/GameIntefaces/IMainGame.h"
#include "Falcon/ResourceManager/ResourceManager.h"
#include <random>

GameplayScreen::GameplayScreen(Falcon::Window *window)
        : m_window(window)
{

}

int GameplayScreen::getNextScreenIndex() const
{
    return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPrevScreenIndex() const
{
    return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::create()
{

}

void GameplayScreen::destroy()
{

}

void GameplayScreen::onEntry()
{
    ImGui_ImplSdl_Init(m_window->getSDLWindow());

    b2Vec2 gravity(0.0f, 0.0f);
    m_world = std::make_unique<b2World>(gravity);

    m_debugRender.init();

    // Load the texture
    m_texture = Falcon::ResourceManager::getTexture("media/Textures/wall_tile.png");

    // Make a bunch of boxes
    std::mt19937 rng;
    std::uniform_real_distribution<float> x_dist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> y_dist(-15.0f, 15.0f);
    std::uniform_real_distribution<float> size(1.0f, 4.0f);

    const int numBoxes = 50;

    for (int i = 0; i < numBoxes; i++)
    {
        Box newBox;
        float boxSize = size(rng);
        newBox.init(m_world.get(), glm::vec2(x_dist(rng), y_dist(rng)), glm::vec2(boxSize, boxSize), m_texture, false);
        m_boxes.push_back(newBox);
    }

    //Init spritebatch
    m_spriteBatch.init();

    // Compile texture shader
    m_shaderProgram.compileShaders("include/Falcon/Shaders/textureShading.vert", "include/Falcon/Shaders/textureShading.frag");
    m_shaderProgram.addAttribute("vertexPosition");
    m_shaderProgram.addAttribute("vertexColor");
    m_shaderProgram.addAttribute("vertexUV");
    m_shaderProgram.linkShaders();

    // Compile light shader
    m_lightProgram.compileShaders("include/Falcon/Shaders/lightShading.vert", "include/Falcon/Shaders/lightShading.frag");
    m_lightProgram.addAttribute("vertexPosition");
    m_lightProgram.addAttribute("vertexColor");
    m_lightProgram.addAttribute("vertexUV");
    m_lightProgram.linkShaders();

    // Init camera
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
    m_camera.setScale(16.0f);

    // Init player
    m_player.init(m_world.get(), glm::vec2(10.0f, 10.0f), glm::vec2(2.0f, 2.0f));

    playerLight.color = Falcon::Color(255, 255, 255, 128);
    playerLight.size = 30.0f;

    mouseLight.color = Falcon::Color(0, 0, 0, 128);
    mouseLight.size = 15.0f;

    m_map.init(100, 100, "media/Textures/terrain.png", 32);
}

void GameplayScreen::onExit()
{
    m_debugRender.dispose();
}

void GameplayScreen::update()
{
    checkInput();
    m_player.update(m_game->inputManager);
    m_camera.setPosition(m_player.getPosition());
    m_camera.update();

    playerLight.position = m_player.getPosition();
    glm::vec2 mousePos = m_camera.screenToWorld(m_game->inputManager.getMouseCoords());
    mouseLight.position = mousePos;

    // Update the physics simulation
    m_world->Step(1.0f / 60.0f, 6, 2);
}

void GameplayScreen::draw()
{
    ImGui_ImplSdl_NewFrame(m_window->getSDLWindow());

    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    m_shaderProgram.use();

    // Upload texture uniform
    GLint textureUniform = m_shaderProgram.getUniformLocation("sampler");
    glUniform1i(textureUniform, 0);

    // Camera matrix
    glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
    GLint pUniform = m_shaderProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
    if (m_map.isGenerated())
    {
        m_map.draw();
    }

    m_spriteBatch.begin();

    for (auto& box : m_boxes)
    {
        box.draw(m_spriteBatch);
    }

    m_player.draw(m_spriteBatch);

    m_spriteBatch.end();

    m_spriteBatch.renderBatch();

    m_shaderProgram.unuse();

    //Debug rendering
    if (m_renderDebug)
    {
        for (auto& box : m_boxes)
        {
            box.drawDebug(m_debugRender);
        }
        m_player.drawDebug(m_debugRender);

        m_debugRender.end();
        m_debugRender.render(projectionMatrix, 2.0f);
    }


    m_lightProgram.use();

    // Additive blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    pUniform = m_shaderProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    m_spriteBatch.begin();

    playerLight.draw(m_spriteBatch);
    mouseLight.draw(m_spriteBatch);

    m_spriteBatch.end();
    m_spriteBatch.renderBatch();

    m_lightProgram.unuse();

    // Reset to regular alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Debug stuff");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    if (ImGui::ColorEdit3("Mouse light color", mouse_color))
    {
        mouseLight.color.r = static_cast<GLubyte>(mouse_color[0] * 255.f);
        mouseLight.color.g = static_cast<GLubyte>(mouse_color[1] * 255.f);
        mouseLight.color.b = static_cast<GLubyte>(mouse_color[2] * 255.f);
    }
    if (ImGui::Button("Debug mode"))
    {
        m_renderDebug = !m_renderDebug;
    }
    if (ImGui::Button("Random mouse color"))
    {
        std::mt19937 rng(time(0));
        std::uniform_int_distribution<int> color(0, 255);
        mouseLight.color.r = static_cast<GLubyte>(color(rng));
        mouseLight.color.g = static_cast<GLubyte>(color(rng));
        mouseLight.color.b = static_cast<GLubyte>(color(rng));
    }
    if (ImGui::Button("Generate random map"))
    {
        m_map.generateMap();
    }
    ImGui::Text("Mouse position (%.2f, %.2f)", m_camera.screenToWorld(m_game->inputManager.getMouseCoords()).x, m_camera.screenToWorld(m_game->inputManager.getMouseCoords()).y);
    ImGui::Text("Camera position (%.2f, %.2f)", m_player.getPosition().x, m_player.getPosition().y);
    ImGui::End();
    ImGui::Render();

}

void GameplayScreen::checkInput()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        m_game->onSDLEvent(e);
        ImGui_ImplSdl_ProcessEvent(&e);
    }
}










#include <iostream>
#include "GameplayScreen.h"
#include "Falcon/GameIntefaces/IMainGame.h"
#include "Falcon/ResourceManager/ResourceManager.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "PlayerInputComponent.h"
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
    m_objectFactory.setWorld(m_world.get());

    m_debugRender.init();
    // Make a bunch of boxes
    std::mt19937 rng(time(0));
    std::uniform_real_distribution<float> x_dist(-10.0f, 10.0f);
    std::uniform_real_distribution<float> y_dist(-15.0f, 15.0f);
    std::uniform_real_distribution<float> size(1.0f, 4.0f);

    const int numBoxes = 50;

    for (int i = 0; i < numBoxes; i++)
    {
        auto box = m_objectFactory.createObject("media/Objects/Box.xml");
        box->getComponent<BodyComponent>()->setPosition(glm::vec2(x_dist(rng), y_dist(rng)));

        m_gameObjects.push_back(box);
    }
    for (int i = 0; i < 5; i++)
    {
        auto circle = m_objectFactory.createObject("media/Objects/Circle.xml");
        circle->getComponent<BodyComponent>()->setPosition(glm::vec2(x_dist(rng), y_dist(rng)));
        m_gameObjects.push_back(circle);
    }

    //Init spritebatch
    m_spriteBatch.init();
    m_lightSpriteBatch.init();

    // Compile texture and light shader
    compileShader(m_textureProgram, "include/Falcon/Shaders/textureShading.vert", "include/Falcon/Shaders/textureShading.frag");
    compileShader(m_lightProgram, "include/Falcon/Shaders/lightShading.vert", "include/Falcon/Shaders/lightShading.frag");

    // Init camera
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
    m_camera.setScale(16.0f);

    // Init player
    m_player.init(m_world.get(), glm::vec2(10.0f, 10.0f), glm::vec2(2.0f, 2.0f));

    //TODO: MAKE PLAYER XML, CREATE THE ANIMATION COMPONENT AND GET THE SHIT DONE IN THE MAP
    auto player = createPlayer(m_world.get(),
                               glm::vec2(15.0f, 10.0f),
                               glm::vec2(0.0f, 1.0f),
                               glm::vec2(2.0f, 2.0f),
                               glm::vec2(4.0f, 4.0f),
                               "media/Textures/Wolfpack.png",
                               Falcon::Color(255, 255, 255, 255),
                               56);

    m_gameObjects.push_back(player);

    playerLight.color = Falcon::Color(62, 96, 111, 0);
    playerLight.size = 100.0f;

    mouseLight.color = Falcon::Color(0, 0, 0, 128);
    mouseLight.size = 15.0f;

    m_map.init(m_world.get(), 200, 200, "media/Textures/terrain.png", 32);
}

void GameplayScreen::onExit()
{
    m_debugRender.dispose();
}

void GameplayScreen::update(float deltaTime)
{
    checkInput();
    m_player.update(m_game->inputManager, deltaTime);
    for (auto& object : m_gameObjects)
    {
        object->update(deltaTime);
    }
    m_camera.setPosition(m_player.getPosition());
    m_camera.update();

    playerLight.position = m_player.getPosition();
    glm::vec2 mousePos = m_camera.screenToWorld(m_game->inputManager.getMouseCoords());
    mouseLight.position = mousePos;

    // Update the physics simulation
    m_world->Step(1.0f / 60.0f, 6, 2);

    if (m_time < 0.0f)
    {
        m_darker = 1;
    } else if (m_time > 0.7f)
    {
        m_darker = -1;
    }
    m_time += m_darker * 0.001f * deltaTime;
    playerLight.color.a = static_cast<GLubyte>(m_time * (255 / 0.7));

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
    GLint colorUniform =  m_textureProgram.getUniformLocation("color");
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
    for (auto& object : m_gameObjects)
    {
        auto spriteComponent = object->getComponent<SpriteComponent>();
        auto collisionComponent = object->getComponent<CollisionComponent>();
        auto bodyComponent = object->getComponent<BodyComponent>();
        if (spriteComponent)
        {
            spriteComponent->draw(m_spriteBatch);
        }
        if (m_renderDebug)
        {
            if (collisionComponent)
            {
                if (bodyComponent->getBody()->GetType() == b2_dynamicBody)
                {
                    collisionComponent->drawDebug(m_debugRender, Falcon::Color(255, 0, 255, 255));
                }
                else
                {

                    collisionComponent->drawDebug(m_debugRender, Falcon::Color(255, 255, 0, 255));
                }
            }

        }
    }
    m_player.draw(m_spriteBatch, deltaTime);
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();

    if (m_map.isGenerated())
    {
        m_map.drawForeground();
    }
    m_textureProgram.unuse();


    //Debug rendering
    if (m_renderDebug)
    {
        m_map.drawDebug(m_debugRender);
        m_player.drawDebug(m_debugRender);

        m_debugRender.end();
        m_debugRender.render(projectionMatrix, 2.0f);
    }


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
    ImGui::Text("Player position (%.2f, %.2f)", m_player.getPosition().x, m_player.getPosition().y);
    ImGui::Text("Time %.5f", m_time);
    ImGui::Text("Player light alpha %i", playerLight.color.a);
    ImGui::Text("Number of objects in the scene %l", m_gameObjects.size());
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
std::shared_ptr<GameObject>
GameplayScreen::createCircle(b2World *world, const glm::vec2 position, const glm::vec2 dimensions, bool fixedRotation, b2BodyType bodyType)
{
    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
    b2CircleShape circleShape;
    circleShape.m_radius = dimensions.x / 2.0f;

    obj->getComponent<BodyComponent>()->init(world, position, dimensions, bodyType, fixedRotation);

    obj->attachComponent<CollisionComponent>();
    obj->getComponent<CollisionComponent>()->init(obj.get(), &circleShape, dimensions);

    return obj;
}

std::shared_ptr<GameObject>
GameplayScreen::createPlayer(b2World *world,
                             const glm::vec2 collisionPosition,
                             const glm::vec2 spritePosition,
                             const glm::vec2 collisionDimensions,
                             const glm::vec2 spriteDimensions,
                             const std::string &texturePath,
                             Falcon::Color color, int spriteID)
{
    auto obj = createCircle(world, collisionPosition, collisionDimensions, true, b2_dynamicBody);
    obj->attachComponent<PlayerInputComponent>();
    obj->getComponent<PlayerInputComponent>()->init(&m_game->inputManager);

    obj->attachComponent<SpriteComponent>();
    obj->getComponent<SpriteComponent>()->init(texturePath, color, spriteDimensions, spritePosition, spriteID);
    return obj;
}


void GameplayScreen::compileShader(Falcon::ShaderProgram& shaderProgram, const std::string &vertPath, const std::string &fragPath)
{
    shaderProgram.compileShaders(vertPath, fragPath);
    shaderProgram.addAttribute("vertexPosition");
    shaderProgram.addAttribute("vertexColor");
    shaderProgram.addAttribute("vertexUV");
    shaderProgram.linkShaders();
}









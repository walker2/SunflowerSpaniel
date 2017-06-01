#include <Falcon/ResourceManager/ResourceManager.h>
#include "MainMenuScreen.h"
#include "ScreenIndices.h"
#include "Falcon/GameIntefaces/IMainGame.h"
#include "../ObjectFactory/ObjectFactory.h"

MainMenuScreen::MainMenuScreen(Falcon::Window *window)
        : m_window(window)
{
    m_screenIndex = SCREEN_INDEX_MAINMENU;
}

int MainMenuScreen::getNextScreenIndex() const
{
    return SCREEN_INDEX_GAMEPLAY;
}

int MainMenuScreen::getPrevScreenIndex() const
{
    return SCREEN_INDEX_NO_SCREEN;
}

void MainMenuScreen::create()
{
    ImGui_ImplSdl_Init(m_window->getSDLWindow());

    //Init spritebatch
    m_spriteBatch.init();
    compileShader(m_textureProgram, "include/Falcon/Shaders/textureShading.vert",
                  "include/Falcon/Shaders/textureShading.frag");

    // Init camera
    m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
    m_camera.setScale(1.0f);
}

void MainMenuScreen::destroy()
{

}

void MainMenuScreen::onEntry()
{
    b2Vec2 gravity(0.0f, 0.0f);
    m_world = std::make_unique<b2World>(gravity);
    ObjectFactory::instance().setWorld(m_world.get());

    auto background = ObjectFactory::instance().createObject("media/Objects/MenuScreen.xml");
    m_gameObjects.push_back(background);

    auto fire = ObjectFactory::instance().createObject("media/Objects/MenuFire.xml");
    m_gameObjects.push_back(fire);

    auto dog = ObjectFactory::instance().createObject("media/Objects/MenuDog.xml");
    m_gameObjects.push_back(dog);

    auto man = ObjectFactory::instance().createObject("media/Objects/MenuMan.xml");
    m_gameObjects.push_back(man);
}

void MainMenuScreen::onExit()
{
    m_gameObjects.clear();
}

void MainMenuScreen::update(float deltaTime)
{
    checkInput();
    m_camera.update();

    for (auto &object : m_gameObjects)
    {
        object->update(deltaTime);
    }

}

void MainMenuScreen::draw(float deltaTime)
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
    glm::vec4 color(1.0, 1.0, 1.0, 1.0);
    GLint colorUniform = m_textureProgram.getUniformLocation("color");
    glUniform4fv(colorUniform, 1, &color[0]);

    // Camera matrix
    glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
    GLint pUniform = m_textureProgram.getUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    m_spriteBatch.begin();
    for (auto &object : m_gameObjects)
    {
        auto spriteComponent = object->getComponent<SpriteComponent>();
        auto animationComponent = object->getComponent<AnimationComponent>();
        auto bodyComponent = object->getComponent<BodyComponent>();

        if (spriteComponent)
        {
            spriteComponent->draw(m_spriteBatch);
        }

        if (animationComponent)
        {
            animationComponent->draw(m_spriteBatch, deltaTime);
        }
    }
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();

    m_textureProgram.unuse();

    bool open = true;

    ImGui::SetNextWindowPos(ImVec2(832, 264));
    if (!ImGui::Begin("Overlay", &open, ImVec2(0, 0), 0.0f,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                      ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::End();
        return;
    }
    ImTextureID textureIDNewGame = reinterpret_cast<void *>(Falcon::ResourceManager::getTexture(
            "media/Textures/ButtonNewGame256x64.png").id);
    ImTextureID textureIDExit = reinterpret_cast<void *>(Falcon::ResourceManager::getTexture(
            "media/Textures/ButtonExit256x64.png").id);
    if (ImGui::ImageButton(textureIDNewGame, ImVec2(256, 64), ImVec2(0, 0), ImVec2(1, 1), 2, ImColor(0, 0, 0, 255)))
    {
        m_currentState = Falcon::ScreenState::CHANGE_NEXT;
    }
    if (ImGui::ImageButton(textureIDExit, ImVec2(256, 64), ImVec2(0, 0), ImVec2(1, 1), 2, ImColor(0, 0, 0, 255)))
    {
        m_currentState = Falcon::ScreenState::EXIT_APP;
    }
    ImGui::End();
    //ImGui::ShowTestWindow(&open);
    ImGui::Render();
}

void MainMenuScreen::compileShader(Falcon::ShaderProgram &shaderProgram, const std::string &vertPath,
                                   const std::string &fragPath)
{
    shaderProgram.compileShaders(vertPath, fragPath);
    shaderProgram.addAttribute("vertexPosition");
    shaderProgram.addAttribute("vertexColor");
    shaderProgram.addAttribute("vertexUV");
    shaderProgram.linkShaders();
}

void MainMenuScreen::checkInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        m_game->onSDLEvent(e);
    }
}


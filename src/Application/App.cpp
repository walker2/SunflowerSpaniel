#include "App.h"
#include <Falcon/GameIntefaces/ScreenList.h>


App::App()
{

}

App::~App()
{

}

void App::onInit()
{

}

void App::addScreens()
{
    m_gameplayScreen = std::make_unique<GameplayScreen>(&m_window);
    m_mainmenuScreen = std::make_unique<MainMenuScreen>(&m_window);

    m_screenList->addScreen(m_mainmenuScreen.get());
    m_screenList->addScreen(m_gameplayScreen.get());
    m_screenList->setScreen(m_mainmenuScreen->getIndex());
}

void App::onExit()
{

}



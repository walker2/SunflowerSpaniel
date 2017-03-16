#ifndef SUNFLOWERSPANIEL_APP_H
#define SUNFLOWERSPANIEL_APP_H

#include <Falcon/GameIntefaces/IMainGame.h>
#include "../Screens/GameplayScreen.h"
#include "../Screens/MainMenuScreen.h"

/**
 * Application class made for managing game screens
 */
class App : public Falcon::IMainGame
{
public:
    /**
     * Default App class constructor
     */
    App();

    ~App();

    /**
     * Method that called when Application first initialized
     */
    void onInit() override;

    /**
     * Method for adding screens into m_screenList
     */
    void addScreens() override;

    /**
     * Method that called on Application exit
     */
    void onExit() override;

private:
    std::unique_ptr<GameplayScreen> m_gameplayScreen = nullptr;
    std::unique_ptr<MainMenuScreen> m_mainmenuScreen = nullptr;
};


#endif

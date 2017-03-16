#ifndef FALCONLATINUM_MAINGAME_H
#define FALCONLATINUM_MAINGAME_H

#include <memory>
#include "../Window/Window.h"
#include "../InputOutput/InputManager.h"

namespace Falcon
{
    class ScreenList;

    class IGameScreen;

    class IMainGame
    {
    public:
        IMainGame();

        virtual ~IMainGame();

        void run();

        void exitGame();

        virtual void onInit() = 0;

        virtual void addScreens() = 0;

        virtual void onExit() = 0;


        void onSDLEvent(SDL_Event &event);

        float getFPS() const
        { return m_FPS; }

    protected:
        bool init();

        bool initSystems();

        virtual void update(float deltaTime);

        virtual void draw(float deltaTime);

        std::unique_ptr<ScreenList> m_screenList;// = nullptr;
        IGameScreen *m_currentScreen = nullptr;
        bool m_isRunning = false;
        float m_FPS = 0.0f;
        Window m_window;

    };
}


#endif

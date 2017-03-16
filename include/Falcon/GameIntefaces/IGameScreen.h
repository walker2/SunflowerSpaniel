#ifndef FALCONLATINUM_IGAMESCREEN_H
#define FALCONLATINUM_IGAMESCREEN_H

#define SCREEN_INDEX_NO_SCREEN -1
namespace Falcon
{
    class IMainGame;

    enum class ScreenState
    {
        NONE,
        RUNNING,
        EXIT_APP,
        CHANGE_NEXT,
        CHANGE_PREV
    };

    class IGameScreen
    {
    public:
        friend class ScreenList;
        IGameScreen() {};
        virtual ~IGameScreen() {};
        //Returns the index of the next or prev screen
        virtual int getNextScreenIndex() const = 0;
        virtual int getPrevScreenIndex() const = 0;

        //Called at beginning and end
        virtual void create() = 0;
        virtual void destroy() = 0;

        //Called when screen enters and exits focus
        virtual void onEntry() = 0;
        virtual void onExit() = 0;

        //Called in the main game loop
        virtual void update(float deltaTime) = 0;
        virtual void draw(float deltaTime) = 0;

        int getIndex() const { return  m_screenIndex; };
        ScreenState getState() const { return m_currentState; };

        void setParentGame(IMainGame* game) { m_game = game; };
        void setRunning()
        {
            m_currentState = ScreenState::RUNNING;
        }



    protected:
        ScreenState m_currentState = ScreenState::NONE;
        IMainGame* m_game = nullptr;
        int m_screenIndex = SCREEN_INDEX_NO_SCREEN;
    };
}




#endif

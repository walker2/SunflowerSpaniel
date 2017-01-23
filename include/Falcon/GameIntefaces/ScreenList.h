#ifndef FALCONLATINUM_SCREENLIST_H
#define FALCONLATINUM_SCREENLIST_H

#include <vector>

namespace Falcon
{
    class IMainGame;
    class IGameScreen;

    class ScreenList
    {
    public:
        ScreenList(IMainGame* game);
        ~ScreenList();

        IGameScreen* moveNext();
        IGameScreen* movePrev();

        void setScreen(int nextScreen);
        void addScreen(IGameScreen* newScreen);

        void destroy();
        IGameScreen* getCurrent();

    protected:
        IMainGame* m_game = nullptr;
        std::vector<IGameScreen*> m_screen;
        int m_currentScreenIndex = -1;
    };


}



#endif

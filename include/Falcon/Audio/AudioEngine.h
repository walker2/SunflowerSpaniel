#ifndef FALCONLATINUM_AUDIOENGINE_H
#define FALCONLATINUM_AUDIOENGINE_H

#include "SDL_mixer.h"
#include <string>
#include <map>

namespace Falcon
{
    class SoundEffect
    {
    public:
        friend class AudioEngine;
        void play(int loops = 0);

    private:
        Mix_Chunk* m_chunk = nullptr;
    };

    class Music
    {
    public:
        friend class AudioEngine;

        void play(int loops = -1);

        static void pause();
        static void stop();
        static void resume();

    private:
        Mix_Music* m_music = nullptr;
    };

    class AudioEngine
    {
    public:
        AudioEngine(){};
        ~AudioEngine(){ destroy(); };

        void init();
        void destroy();

        SoundEffect loadSoundEffect(const std::string &filePath);
        Music loadMusic(const std::string &filePath);

    private:
        bool m_isInit = false;
        std::map<std::string, Mix_Chunk*> m_soundMap;
        std::map<std::string, Mix_Music*> m_musicMap;

    };

}



#endif //FALCONLATINUM_AUDIOENGINE_H

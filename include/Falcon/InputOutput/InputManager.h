#ifndef FALCONLATINUM_INPUTMANAGER_H
#define FALCONLATINUM_INPUTMANAGER_H

#include <unordered_map>
#include <glm/vec2.hpp>

namespace Falcon
{
    class InputManager
    {
    public:
        static InputManager& instance()
        {
            static InputManager *instance = new InputManager();
            return *instance;
        }

    public:
        void update();

        void pressKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);
        void setMouseCoords(float x, float y);

        /// Returns true if the key is held down
        bool isKeyDown(unsigned int keyID);

        /// Returns true if the key was just pressed
        bool isKeyPressed(unsigned int keyID);

        glm::vec2 getMouseCoords() const { return m_mouseCoords; };

    private:
        /// Returns true if the key is held down
        bool wasKeyDown(unsigned int keyID);

    private:

        std::unordered_map<unsigned int, bool> m_keyMap;
        std::unordered_map<unsigned int, bool> _previousKeyMap;

        glm::vec2 m_mouseCoords;

    private:
        InputManager() {}
    };
}

#endif
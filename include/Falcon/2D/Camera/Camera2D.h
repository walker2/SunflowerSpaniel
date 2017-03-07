#ifndef FALCONLATINUM_CAMERA2D_H
#define FALCONLATINUM_CAMERA2D_H

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace Falcon
{
    class Camera2D
    {
    public:
    Camera2D() : m_screenWidth(500), m_screenHeight(500), m_shouldUpdate(true), m_scale(1.0f), m_position(0.0f, 0.0f), m_cameraMatrix(1.0f), m_orthoMatrix(1.0f)
                      {};
        ~Camera2D() {};

        void init(int screenWidth, int screenHeight);

        void update();
        glm::vec2 screenToWorld(glm::vec2 screenCoords);

        void setPosition(const glm::vec2 &newPosition) { m_position = newPosition; m_shouldUpdate = true; };
        void setScale(float newScale) { m_scale = newScale; m_shouldUpdate = true; };

        glm::vec2 getPosition() { return m_position; };
        float getScale() { return m_scale; };
        glm::mat4 getCameraMatrix() { return m_cameraMatrix; };
        bool isBoxVisible(const glm::vec2 &position, const glm::vec2 &dimensions);

    private:
        int m_screenWidth, m_screenHeight;
        bool m_shouldUpdate;
        float m_scale;
        glm::vec2 m_position;
        glm::mat4 m_cameraMatrix;
        glm::mat4 m_orthoMatrix;
    };

}
#endif

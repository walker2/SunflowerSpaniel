#ifndef FALCONLATINUM_SPRITE_H
#define FALCONLATINUM_SPRITE_H

#include <GL/glew.h>
#include "GLTexture.h"

#include <string>
namespace Falcon
{
    class Sprite
    {
    public:
        Sprite() : m_vboID(0) {};

        ~Sprite();

        void init(float x, float y, float width, float height, std::string texturePath);

        void draw();

    private:
        float m_x;
        float m_y;
        float m_width;
        float m_height;
        GLuint m_vboID;
        GLTexture m_texture;
    };

}
#endif //FALCONLATINUM_SPRITE_H

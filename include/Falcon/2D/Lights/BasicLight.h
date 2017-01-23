#ifndef FALCONLATINUM_BASICLIGHT_H
#define FALCONLATINUM_BASICLIGHT_H

#include "../Vertex.h"
#include "../SpriteBatch/SpriteBatch.h"
#include <glm/glm.hpp>

namespace Falcon
{
    class BasicLight
    {
    public:
        void draw(SpriteBatch& spriteBatch)
        {
            glm::vec4 destRect;
            destRect.x = position.x - size / 2.0f;
            destRect.y =position.y - size / 2.0f;
            destRect.z = size;
            destRect.w = size;
            spriteBatch.draw(destRect, glm::vec4(-1.0f, -1.0f, 2.0f, 2.0f), 0, 0.0f, color, 0);
        }


        Color color;
        glm::vec2 position;
        float size;
    };
}



#endif

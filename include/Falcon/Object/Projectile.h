#ifndef FALCONLATINUM_PROJECTILE_H
#define FALCONLATINUM_PROJECTILE_H


#include <glm/vec2.hpp>
#include "../2D/SpriteBatch/SpriteBatch.h"

namespace Falcon
{
    class Projectile
    {
    public:
        Projectile(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime)
                : m_position(position), m_direction(direction), m_speed(speed), m_lifeTime(lifeTime){};
        ~Projectile() {};

        void draw(Falcon::SpriteBatch& spriteBatch);
        bool update(); //Returns true when should be destroyed

    private:
        int m_lifeTime;
        float m_speed;
        glm::vec2 m_direction;
        glm::vec2 m_position;
    };
}



#endif
#ifndef SUNFLOWERSPANIEL_PLAYER_H
#define SUNFLOWERSPANIEL_PLAYER_H


#include "Circle.h"
#include "Falcon/InputOutput/InputManager.h"
#include "Falcon/2D/TileSheet.h"

enum class DIRECTION { LEFT = 0, RIGHT, UP, DOWN};

class Player
{
public:
    Player();
    ~Player() {};

    void init(b2World *world, const glm::vec2 position, const glm::vec2 dimensions);

    void draw(Falcon::SpriteBatch& spriteBatch);
    void drawDebug(Falcon::DebugRenderer &debugRenderer);

    void update(Falcon::InputManager& inputManager);

    const Circle& getCircle() const { return m_circle; };
    glm::vec2 getPosition() const
    {
        glm::vec2 pos;
        pos.x = m_circle.getBody()->GetPosition().x;
        pos.y = m_circle.getBody()->GetPosition().y;

        return pos;
    }

private:
    float m_animTime = 0.0f;

    DIRECTION m_direction = DIRECTION::LEFT;
    Falcon::TileSheet m_tileSheet;
    Circle m_circle;
};


#endif

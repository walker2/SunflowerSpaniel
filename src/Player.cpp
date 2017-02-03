#include "Player.h"
#include "Falcon/ResourceManager/ResourceManager.h"
#include "CollisionComponent.h"

Player::Player()
{

}

void Player::init(b2World *world, const glm::vec2 position, const glm::vec2 dimensions)
{
    m_animSpeed = 0.1;
    Falcon::GLTexture texture = Falcon::ResourceManager::getTexture("media/Textures/Wolfpack.png");

    m_circle.init(world, position, dimensions, true, b2_dynamicBody);

    m_tileSheet.init(texture, glm::ivec2(texture.width / 32, texture.height / 32));
}

void Player::draw(Falcon::SpriteBatch& spriteBatch, float deltaTime)
{
    glm::vec4 destRect;
    b2Body* body = m_circle.getComponent<BodyComponent>()->getBody();

    int tileIndex;
    int frameCount;

    switch (m_direction)
    {
        case DIRECTION::LEFT:
            tileIndex = 56;
            break;
        case DIRECTION::RIGHT:
            tileIndex = 48;
            break;
        case DIRECTION::UP:
            tileIndex = 32;
            break;
        case DIRECTION::DOWN:
            tileIndex = 40;
            break;
    }

    if (abs(body->GetLinearVelocity().x) > 1.0f || abs(body->GetLinearVelocity().y) > 1.0f )
    {
        frameCount = 4;
    }
    else
    {
        frameCount = 1;
    }

    // Increment animation tile
    m_animTime += m_animSpeed * deltaTime;

    // Apply animation
    tileIndex = tileIndex + (int)m_animTime % frameCount;
    auto dims = m_circle.getComponent<CollisionComponent>()->getDimensions();

    destRect.x = body->GetPosition().x - dims.x;
    destRect.y = body->GetPosition().y - dims.y / 2.0f;
    destRect.z = dims.x * 2.0f;
    destRect.w = dims.y * 2.0f;
    spriteBatch.draw(destRect, m_tileSheet.getUVs(tileIndex), m_tileSheet.texture.id, 0.0f, Falcon::Color(255, 255, 225, 255), body->GetAngle());
}

void Player::update(Falcon::InputManager &inputManager, float deltaTime)
{
    b2Body* body = m_circle.getComponent<BodyComponent>()->getBody();
    b2Vec2 movementSpeed(0.0f, 0.0f);

    if (inputManager.isKeyDown(SDLK_a))
    {
        movementSpeed.x += -1;
        m_direction = DIRECTION::LEFT;

    }
    else if (inputManager.isKeyDown(SDLK_d))
    {
        movementSpeed.x += 1;
        m_direction = DIRECTION::RIGHT;
    }

    if (inputManager.isKeyDown(SDLK_w))
    {
        movementSpeed.y += 1;
        m_direction = DIRECTION::UP;
    }
    else if (inputManager.isKeyDown(SDLK_s))
    {
        movementSpeed.y += -1 ;
        m_direction = DIRECTION::DOWN;
    }

    float length = movementSpeed.Length();
    if (length != 0)
    {
        movementSpeed.x /= length;
        movementSpeed.y /= length;
    }
    movementSpeed *= m_speed * deltaTime;
    body->SetLinearVelocity(movementSpeed);
    body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.7f,
                                   body->GetLinearVelocity().y * 0.7f));
}

void Player::drawDebug(Falcon::DebugRenderer &debugRenderer)
{
    m_circle.drawDebug(debugRenderer);
}


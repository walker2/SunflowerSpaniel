#include "Player.h"
#include "Falcon/ResourceManager/ResourceManager.h"

Player::Player()
{

}

void Player::init(b2World *world, const glm::vec2 position, const glm::vec2 dimensions)
{
    Falcon::GLTexture texture = Falcon::ResourceManager::getTexture("media/Textures/Wolfpack.png");

    m_circle.init(world, position, dimensions, true);

    m_tileSheet.init(texture, glm::ivec2(texture.width / 32, texture.height / 32));
}

void Player::draw(Falcon::SpriteBatch& spriteBatch)
{
    glm::vec4 destRect;
    b2Body* body = m_circle.getBody();
    int tileIndex;
    int numTiles = 1;

    float animSpeed = 0.2;
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
        numTiles = 4;
    }
    else
    {
        numTiles = 1;
    }


    // Increment animation tile
    m_animTime += animSpeed;

    // Apply animation
    tileIndex = tileIndex + (int)m_animTime % numTiles;

    destRect.x = body->GetPosition().x - m_circle.getDimensions().x;
    destRect.y = body->GetPosition().y - m_circle.getDimensions().y / 2.0f;
    destRect.z = m_circle.getDimensions().x * 2.0f;
    destRect.w = m_circle.getDimensions().y * 2.0f;
    spriteBatch.draw(destRect, m_tileSheet.getUVs(tileIndex), m_tileSheet.texture.id, 0.0f, Falcon::Color(255, 255, 225, 255), body->GetAngle());
}

void Player::update(Falcon::InputManager &inputManager)
{
    b2Body* body = m_circle.getBody();
    if (inputManager.isKeyDown(SDLK_a))
    {
        body->SetLinearVelocity(b2Vec2(-20.0f, 0.0f));
        m_direction = DIRECTION::LEFT;
    }
    else if (inputManager.isKeyDown(SDLK_d))
    {
        body->SetLinearVelocity(b2Vec2(20.0f, 0.0f));
        m_direction = DIRECTION::RIGHT;
    }

    if (inputManager.isKeyDown(SDLK_w))
    {
        body->SetLinearVelocity(b2Vec2(0.0f, 20.0f));
        m_direction = DIRECTION::UP;
    }
    else if (inputManager.isKeyDown(SDLK_s))
    {
        body->SetLinearVelocity(b2Vec2(0.0f, -20.0f));
        m_direction = DIRECTION::DOWN;
    }

    body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.7f,
                                   body->GetLinearVelocity().y * 0.7f));


}

void Player::drawDebug(Falcon::DebugRenderer &debugRenderer)
{
    m_circle.drawDebug(debugRenderer);
}

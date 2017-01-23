#include "Circle.h"

void Circle::init(b2World *world, const glm::vec2 position, const glm::vec2 dimensions, bool fixedRotation)
{
    m_dimensions = dimensions;

    // Make the body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation = fixedRotation;

    m_body = world->CreateBody(&bodyDef);
    m_body->SetLinearDamping(2.0f);

    //Create the circle
    b2CircleShape circleShape;
    circleShape.m_radius = dimensions.x / 2.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    m_fixture = m_body->CreateFixture(&fixtureDef);
}

void Circle::drawDebug(Falcon::DebugRenderer &debugRenderer) const
{
    glm::vec4 destRect;
    destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;
    destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;
    destRect.z = m_dimensions.x;
    destRect.w = m_dimensions.y;
    //debugRenderer.drawBox(destRect, Falcon::Color(255, 255, 255, 255), m_body->GetAngle());
    debugRenderer.drawCircle(glm::vec2(destRect.x + m_dimensions.x / 2.0f, destRect.y + m_dimensions.y / 2.0f),
                             Falcon::Color(255, 255, 255, 255), m_dimensions.x / 2.0f);
}

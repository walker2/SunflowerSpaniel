#include "Circle.h"
#include "CollisionComponent.h"


Circle::Circle()
{
    attachComponent<BodyComponent>();
    attachComponent<CollisionComponent>();
}

void Circle::init(b2World *world, const glm::vec2 position, const glm::vec2 dimensions, bool fixedRotation, b2BodyType bodyType)
{
    auto bodyComponent = getComponent<BodyComponent>();
    getComponent<CollisionComponent>()->setDimensions(dimensions);

    // Make the body
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation = fixedRotation;

    bodyComponent->setBody(world->CreateBody(&bodyDef));
    bodyComponent->getBody()->SetLinearDamping(2.0f);

    //Create the circle
    b2CircleShape circleShape;
    circleShape.m_radius = dimensions.x / 2.0f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    bodyComponent->getBody()->CreateFixture(&fixtureDef);
}

void Circle::drawDebug(Falcon::DebugRenderer &debugRenderer)
{
    auto body = getComponent<BodyComponent>()->getBody();
    auto dims = getComponent<CollisionComponent>()->getDimensions();

    glm::vec4 destRect;
    destRect.x = body->GetPosition().x - dims.x / 2.0f;
    destRect.y = body->GetPosition().y - dims.y / 2.0f;
    destRect.z = dims.x;
    destRect.w = dims.y;
    debugRenderer.drawCircle(glm::vec2(destRect.x + dims.x / 2.0f, destRect.y + dims.y / 2.0f),
                             Falcon::Color(255, 255, 255, 255), dims.x / 2.0f);
}

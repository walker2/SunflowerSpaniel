#ifndef SUNFLOWERSPANIEL_COLLISIONCOMPONENT_H
#define SUNFLOWERSPANIEL_COLLISIONCOMPONENT_H


#include <Box2D/Box2D.h>
#include <Falcon/2D/DebugRenderer/DebugRenderer.h>
#include "GameObject.h"
class CollisionComponent : public Component
{
public:
    CollisionComponent() {};

    void init(tinyxml2::XMLNode *pNode) override
    {
        m_body = m_obj->getComponent<BodyComponent>()->getBody();

        tinyxml2::XMLElement *pDimensionsElement = pNode->FirstChildElement("Dimensions");
        float height = 0;
        float width = 0;

        if (pDimensionsElement)
        {
            pDimensionsElement->QueryFloatAttribute("height", &height);
            pDimensionsElement->QueryFloatAttribute("width", &width);
            m_dimensions.x = width;
            m_dimensions.y = height;
        }

        tinyxml2::XMLElement *pShapeElement = pNode->FirstChildElement("Shape");

        b2PolygonShape boxShape;
        boxShape.SetAsBox(m_dimensions.x / 2.0f, m_dimensions.y / 2.0f);
        b2CircleShape circleShape;
        circleShape.m_radius = m_dimensions.x / 2.0f;

        b2FixtureDef fixtureDef;
        if (pShapeElement)
        {
            std::string type = pShapeElement->Attribute("name");
            if (type == "Box")
            {
                fixtureDef.shape = &boxShape;
            } else if (type == "Circle")
            {
                fixtureDef.shape = &circleShape;
            }

            tinyxml2::XMLElement *pDensity = pShapeElement->FirstChildElement("Density");
            float density = 0;
            if (pDensity)
            {
                pDensity->QueryFloatText(&density);
            }
            fixtureDef.density = density;

            tinyxml2::XMLElement *pFriction = pShapeElement->FirstChildElement("Friction");
            float friction = 0;
            if (pFriction)
            {
                pFriction->QueryFloatText(&friction);
            }
            fixtureDef.friction = friction;

        }
        m_fixture = m_body->CreateFixture(&fixtureDef);
    }

    void init(GameObject* obj, b2Shape* shape, const glm::vec2 dimensions)
    {
        m_body = obj->getComponent<BodyComponent>()->getBody();
        m_dimensions = dimensions;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        m_fixture = m_body->CreateFixture(&fixtureDef);
    }
    void update(GameObject* obj, float deltaTime)
    {
        m_body = obj->getComponent<BodyComponent>()->getBody();
    }
    // Maybe this should be another component but this seems logical enough
    void drawDebug(Falcon::DebugRenderer &debugRenderer, Falcon::Color color)
    {
        if (m_fixture->GetShape()->GetType() == b2Shape::Type::e_polygon)
        {
            glm::vec4 destRect;
            destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;
            destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;
            destRect.z = m_dimensions.x;
            destRect.w = m_dimensions.y;
            debugRenderer.drawBox(destRect, color, m_body->GetAngle());
        }
        else if (m_fixture->GetShape()->GetType() == b2Shape::Type::e_circle)
        {
            glm::vec4 destRect;
            destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;
            destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;
            destRect.z = m_dimensions.x;
            destRect.w = m_dimensions.y;
            debugRenderer.drawCircle(glm::vec2(destRect.x + m_dimensions.x / 2.0f, destRect.y + m_dimensions.y / 2.0f),
                                     color, m_dimensions.x / 2.0f);
        }
    }


    b2Fixture* getFixture() const { return m_fixture; };
    glm::vec2 getDimensions() const { return m_dimensions; };

    void setFixture(b2Fixture* fixture) { m_fixture = fixture; };
    void setDimensions(glm::vec2 dims)
    {
        m_dimensions = dims;
    };
    void setObject(GameObject* obj) { m_obj = obj; }
private:
    GameObject* m_obj;
    b2Fixture* m_fixture;
    b2Body* m_body = nullptr;
    glm::vec2 m_dimensions;
};


#endif

#include "BodyComponent.h"

void BodyComponent::init(tinyxml2::XMLNode *pNode)
{
    b2BodyDef bodyDef;

    tinyxml2::XMLElement *pPositionElement = pNode->FirstChildElement("Position");
    float x = 0.0f;
    float y = 0.0f;

    if (pPositionElement)
    {
        pPositionElement->QueryFloatAttribute("x", &x);
        pPositionElement->QueryFloatAttribute("y", &y);
        bodyDef.position.Set(x, y);
    } else
    {
        bodyDef.position.Set(x, y);
    }

    tinyxml2::XMLElement *pBodyTypeElement = pNode->FirstChildElement("BodyType");
    if (pBodyTypeElement)
    {
        std::string type = pBodyTypeElement->FirstChild()->Value();
        if (type == "Dynamic")
        {
            bodyDef.type = b2BodyType::b2_dynamicBody;
        } else if (type == "Kinematic")
        {
            bodyDef.type = b2BodyType::b2_kinematicBody;
        } else
        {
            bodyDef.type = b2BodyType::b2_staticBody;
        }
    } else
    {
        bodyDef.type = b2BodyType::b2_dynamicBody;
    }

    tinyxml2::XMLElement *pRotationElement = pNode->FirstChildElement("FixedRotation");
    bool fixedRotation = false;
    if (pRotationElement)
    {
        pRotationElement->QueryBoolText(&fixedRotation);
        bodyDef.fixedRotation = fixedRotation;
    } else
    {
        bodyDef.fixedRotation = fixedRotation;
    }

    tinyxml2::XMLElement *pDampingElement = pNode->FirstChildElement("LinearDamping");
    float damping = 0.0f;
    if (pDampingElement)
    {
        pDampingElement->QueryFloatText(&damping);
        bodyDef.linearDamping = damping;
    }
    m_body = m_world->CreateBody(&bodyDef);

}

void BodyComponent::init(b2World *world, const glm::vec2 position, const glm::vec2 /*dimensions*/, b2BodyType bodyType,
                         bool fixedRotation)
{
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation = fixedRotation;

    m_body = world->CreateBody(&bodyDef);
    m_body->SetLinearDamping(2.0f);
}

glm::vec2 BodyComponent::getPosition()
{
    glm::vec2 pos;
    pos.x = m_body->GetPosition().x;
    pos.y = m_body->GetPosition().y;

    return pos;
}

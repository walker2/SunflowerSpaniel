#include "SensorComponent.h"

void SensorComponent::init(tinyxml2::XMLNode *pNode)
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
        fixtureDef.isSensor = true;

    }
    m_fixture = m_body->CreateFixture(&fixtureDef);
}

void SensorComponent::update(GameObject *obj, float /*deltaTime*/)
{
    if (!m_isEnabled)
        return;

    m_body = obj->getComponent<BodyComponent>()->getBody();
}

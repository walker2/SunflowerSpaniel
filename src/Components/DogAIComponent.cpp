#include "DogAIComponent.h"

void DogAIComponent::update(GameObject *obj, float deltaTime)
{
    auto body = obj->getComponent<BodyComponent>()->getBody();
    m_position.x = body->GetPosition().x;
    m_position.y = body->GetPosition().y;

    m_thirst += 0.0004f * deltaTime;
    m_hunger += 0.00008f * deltaTime;
    m_manager->update();

    if (m_shouldMove)
    {
        if (obj->getComponent<PlayerInputComponent>()->isEnabled())
            return;

        auto human = ObjectFactory::instance().getObjectFromID(ObjectFactory::instance().getHumanPlayerID());
        if (human != nullptr)
        {
            m_direction = glm::normalize(human->getComponent<BodyComponent>()->getPosition() - m_position);
            m_position += m_direction * 20.f * deltaTime;
            body->SetTransform(b2Vec2(m_position.x, m_position.y), body->GetAngle());
        }
    }

}

void DogAIComponent::init(tinyxml2::XMLNode *pNode)
{
    tinyxml2::XMLElement *pFontElement = pNode->FirstChildElement("Font");
    if (pFontElement)
    {
        std::string filePath = pFontElement->GetText();
        int size = 0;
        pFontElement->QueryIntAttribute("size", &size);
        m_spriteFont = new Falcon::SpriteFont(filePath.c_str(), size);
    }
}

void DogAIComponent::draw(Falcon::SpriteBatch &spriteBatch, float deltaTime)
{
    m_spriteFont->draw(spriteBatch, m_text.c_str(), m_position, glm::vec2(0.1), 0.0f, Falcon::Color(255, 255, 255, 255));
}

void DogAIComponent::handleMessage(const Telegram &telegram)
{
    m_manager->handleMessage(telegram);
}

void DogAIComponent::moveToTheHuman()
{
    auto human = ObjectFactory::instance().getObjectFromID(ObjectFactory::instance().getHumanPlayerID());

    glm::vec2 distVec = human->getComponent<BodyComponent>()->getPosition() - m_position;
    float distance = glm::length(distVec);

    m_shouldMove = distance > 50;
}

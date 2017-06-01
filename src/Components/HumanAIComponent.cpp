#include "HumanAIComponent.h"

void HumanAIComponent::update(GameObject *obj, float deltaTime)
{
    auto body = obj->getComponent<BodyComponent>()->getBody();
    m_position.x = body->GetPosition().x;
    m_position.y = body->GetPosition().y;

    m_thirst += 0.0004f * deltaTime;
    m_hunger += 0.00008f * deltaTime;
    m_manager->update();
}

void HumanAIComponent::init(tinyxml2::XMLNode *pNode)
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

void HumanAIComponent::draw(Falcon::SpriteBatch &spriteBatch, float deltaTime)
{
    m_spriteFont->draw(spriteBatch, m_text.c_str(), m_position, glm::vec2(0.1), 0.0f,
                       Falcon::Color(255, 255, 255, 255));
}

void HumanAIComponent::handleMessage(const Telegram &telegram)
{
    m_manager->handleMessage(telegram);
}


#include <ImGUI/imgui.h>
#include "InteractiveComponent.h"
#include "../ObjectFactory/ObjectFactory.h"
#include "../Messaging/Messages.h"
#include "../Messaging/MessageManager.h"
#include "InventoryComponent.h"

void InteractiveComponent::init(tinyxml2::XMLNode *pNode)
{
    tinyxml2::XMLElement *pFontElement = pNode->FirstChildElement("Font");
    if (pFontElement)
    {
        std::string filePath = pFontElement->GetText();
        int size = 0;
        pFontElement->QueryIntAttribute("size", &size);
        m_spriteFont = new Falcon::SpriteFont(filePath.c_str(), size);
    }

    tinyxml2::XMLElement *pTextElement = pNode->FirstChildElement("Text");
    if (pTextElement)
    {
        m_text = pTextElement->GetText();
        pTextElement->QueryFloatAttribute("scale", &m_textScale);
    }

    tinyxml2::XMLElement *pColorElement = pNode->FirstChildElement("Color");
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 0;
    if (pColorElement)
    {
        pColorElement->QueryIntAttribute("r", &r);
        pColorElement->QueryIntAttribute("g", &g);
        pColorElement->QueryIntAttribute("b", &b);
        pColorElement->QueryIntAttribute("a", &a);
        Falcon::Color color(r, g, b, a);
        m_color = color;
    }
    tinyxml2::XMLElement *pInteractionKeyElement = pNode->FirstChildElement("InteractionKey");
    if (pInteractionKeyElement)
    {
        m_interactionKeyID = static_cast<unsigned>(SDL_GetKeyFromName(pInteractionKeyElement->GetText()));
    }

    tinyxml2::XMLElement *pInteractionType = pNode->FirstChildElement("InteractionType");
    if (pInteractionType)
    {
        std::string type = pInteractionType->GetText();
        m_interactionType = type;
    }
}

void InteractiveComponent::update(GameObject *obj, float)
{
    auto body = obj->getComponent<BodyComponent>()->getBody();
    m_position.x = body->GetPosition().x;
    m_position.y = body->GetPosition().y;
    if (m_visible)
    {
        if (ImGui::IsKeyDown(m_interactionKeyID))
        {
            if (m_interactionType == "Spawn")
            {
                MessageManager::instance().dispatchMsg(0, this->getObject()->getID(), this->getObject()->getID(),
                                                       Message::PLAYER_SPAWNS_NEW_OBJECT, nullptr);
            } else if (m_interactionType == "Pickup")
            {
                MessageManager::instance().dispatchMsg(0, this->getObject()->getID(),
                                                       ObjectFactory::instance().getCurrentPlayerID(), //should be current i suppose
                                                       Message::PLAYER_PICK_UPS_OBJECT, nullptr);
                ObjectFactory::instance().deleteObject(obj);
            } else if (m_interactionType == "Talk")
            {
                MessageManager::instance().dispatchMsg(0,  this->getObject()->getID(), this->getObject()->getID(),
                                                       Message::PLAYER_TALKED, nullptr);
            }
            m_visible = false;
        }
    }
}

void InteractiveComponent::draw(Falcon::SpriteBatch &spriteBatch, float)
{


    if (m_visible)
    {
        m_spriteFont->draw(spriteBatch, m_text.c_str(), m_position, glm::vec2(m_textScale), 0.0f, m_color);
    }
}

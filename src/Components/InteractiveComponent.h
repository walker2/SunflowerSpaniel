#ifndef SUNFLOWERSPANIEL_INTERACTIVECOMPONENT_H
#define SUNFLOWERSPANIEL_INTERACTIVECOMPONENT_H


#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include <Falcon/InputOutput/InputManager.h>
#include "Falcon/2D/SpriteFont/SpriteFont.h"
#include "Component.h"
#include "../ObjectFactory/GameObject.h"
#include "../ObjectFactory/ObjectFactory.h"

class InteractiveComponent : public Component
{
public:
    void init(tinyxml2::XMLNode *pNode) override
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

    void update(GameObject *obj, float deltaTime) override
    {
        auto body = obj->getComponent<BodyComponent>()->getBody();
        m_position.x = body->GetPosition().x;
        m_position.y = body->GetPosition().y;
        if (m_visible)
        {
            if (Falcon::InputManager::instance().isKeyPressed(m_interactionKeyID))
            {
                if (m_interactionType == "Spawn")
                {
                    obj->send(Message::PLAYER_SPAWNS_NEW_OBJECT);
                }
                else if (m_interactionType == "Pickup")
                {
                    obj->send(Message::PLAYER_PICK_UPS_OBJECT);
                    body->GetWorld()->DestroyBody(body);
                    obj->destroy();

                }
                m_visible = false;
            }
        }
    }

    virtual void draw(Falcon::SpriteBatch& spriteBatch, float deltaTime)
    {
        if (m_visible)
        {
            m_spriteFont->draw(spriteBatch, m_text.c_str(), m_position, glm::vec2(m_textScale), 0.0f, m_color);
        }
    }

    void startContact() { m_visible = true; };
    void endContact() { m_visible = false; };

private:
    unsigned int m_interactionKeyID = 0;
    std::string m_interactionType;
    Falcon::SpriteFont* m_spriteFont;
    std::string m_text;
    glm::vec2 m_position;
    Falcon::Color m_color;
    float m_textScale;
    bool m_visible;
};


#endif

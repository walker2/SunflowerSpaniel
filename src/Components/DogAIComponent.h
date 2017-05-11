#ifndef SUNFLOWERSPANIEL_DOGAICOMPONENT_H
#define SUNFLOWERSPANIEL_DOGAICOMPONENT_H

#include <Falcon/2D/SpriteFont/SpriteFont.h>
#include "Component.h"
#include "../FSM/StateManager.h"
#include "../States/DogOwnedStates.h"
#include "../ObjectFactory/GameObject.h"
#include "../FSM/State.h"
#include "NeedsComponent.h"

struct Telegram;

class DogAIComponent : public NeedsComponent
{
public:
    DogAIComponent(GameObject *obj) : NeedsComponent(obj)
    {
        m_manager = std::make_shared<StateManager<DogAIComponent>>(this);
        m_manager->setCurrentState(LayDownAndRest::instance());
    }

    void update(GameObject *obj, float deltaTime) override
    {
        auto body = obj->getComponent<BodyComponent>()->getBody();
        m_position.x = body->GetPosition().x;
        m_position.y = body->GetPosition().y;

        m_thirst += 0.0004f * deltaTime;
        m_hunger += 0.00008f * deltaTime;
        m_manager->update();
    }

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
    }

    virtual void draw(Falcon::SpriteBatch &spriteBatch, float deltaTime)
    {
        m_spriteFont->draw(spriteBatch, m_text.c_str(), m_position, glm::vec2(0.1), 0.0f, Falcon::Color(255, 255, 255, 255));
    }

    void handleMessage(const Telegram &telegram) override
    {
        m_manager->handleMessage(telegram);
    }

    void printMessage(const std::string &text)
    { m_text = text; }

    std::shared_ptr<StateManager<DogAIComponent>> getFSM()
    { return  m_manager; }


private:
    std::shared_ptr<StateManager<DogAIComponent>> m_manager;
    Falcon::SpriteFont *m_spriteFont;
    std::string m_text = "";
    glm::vec2 m_position;
};


#endif
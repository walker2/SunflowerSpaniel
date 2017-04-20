#ifndef SUNFLOWERSPANIEL_DOGAICOMPONENT_H
#define SUNFLOWERSPANIEL_DOGAICOMPONENT_H

#include <Falcon/2D/SpriteFont/SpriteFont.h>
#include "Component.h"
#include "../FSM/StateManager.h"
#include "../States/DogOwnedStates.h"
#include "../ObjectFactory/GameObject.h"
#include "../FSM/State.h"

struct Telegram;

class DogAIComponent : public Component
{
public:
    DogAIComponent(GameObject *obj) : Component(obj)
    {
        m_manager = std::make_shared<StateManager<DogAIComponent>>(this);
        m_manager->setCurrentState(LayDownAndRest::instance());
    }

    void update(GameObject *obj, float deltaTime) override
    {
        auto body = obj->getComponent<BodyComponent>()->getBody();
        m_position.x = body->GetPosition().x;
        m_position.y = body->GetPosition().y;

        m_thirst += 0.001f * deltaTime;
        m_hunger += 0.001f * deltaTime;
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
        m_spriteFont->draw(spriteBatch, m_text.c_str(), m_position, glm::vec2(0.125), 0.0f, Falcon::Color(255, 255, 255, 255));
    }

    void handleMessage(const Telegram &telegram) override
    {
        m_manager->handleMessage(telegram);
    }

    bool isThirsty()
    { return m_thirst > 0.25f; }

    bool isHungry()
    { return m_thirst > 0.5f; }

    bool isFatigued()
    { return m_fatigue > 1; }

    float getThirst()
    { return m_thirst; }

    float getHunger()
    { return m_hunger; }

    float getFatigue()
    { return m_fatigue; }

    bool isLoneley()
    { return m_love < 10; }

    void decreaseFatigue()
    { m_fatigue -= 0.001f; }

    void increaseFatigue()
    { m_fatigue += 0.001f; }

    void decreaseLove()
    { m_love -= 0.001f; }

    void increaseLove()
    { m_love += 0.001f; }

    void printMessage(const std::string &text)
    { m_text = text; }

    std::shared_ptr<StateManager<DogAIComponent>> getFSM()
    { return  m_manager; }


private:
    std::shared_ptr<StateManager<DogAIComponent>> m_manager;
    float m_thirst = 0;
    float m_hunger = 0;
    float m_fatigue = 0;
    float m_love = 10;
    Falcon::SpriteFont *m_spriteFont;
    std::string m_text = "";
    glm::vec2 m_position;
};


#endif

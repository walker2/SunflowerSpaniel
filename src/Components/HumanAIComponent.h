#ifndef SUNFLOWERSPANIEL_HUMANAICOMPONENT_H
#define SUNFLOWERSPANIEL_HUMANAICOMPONENT_H

#include <Falcon/2D/SpriteFont/SpriteFont.h>
#include "Component.h"
#include "../FSM/StateManager.h"
#include "../States/HumanOwnedStates.h"
#include "../ObjectFactory/GameObject.h"
#include "../FSM/State.h"
#include "NeedsComponent.h"

struct Telegram;

class HumanAIComponent : public NeedsComponent
{

public:
    HumanAIComponent(GameObject *obj) : NeedsComponent(obj)
    {
        m_manager = std::make_shared<StateManager<HumanAIComponent>>(this);
        m_manager->setCurrentState(Hunt::instance());
    }

    void update(GameObject *obj, float deltaTime) override;

    void init(tinyxml2::XMLNode *pNode) override;

    virtual void draw(Falcon::SpriteBatch &spriteBatch, float deltaTime);

    void handleMessage(const Telegram &telegram) override;

    void printMessage(const std::string &text)
    { m_text = text; }

    std::shared_ptr<StateManager<HumanAIComponent>> getFSM()
    { return m_manager; }


private:
    std::shared_ptr<StateManager<HumanAIComponent>> m_manager;
    Falcon::SpriteFont *m_spriteFont;
    std::string m_text = "";
    glm::vec2 m_position;
};


#endif

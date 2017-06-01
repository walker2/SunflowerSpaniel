#ifndef SUNFLOWERSPANIEL_DOGAICOMPONENT_H
#define SUNFLOWERSPANIEL_DOGAICOMPONENT_H

#include <Falcon/2D/SpriteFont/SpriteFont.h>
#include "Component.h"
#include "../FSM/StateManager.h"
#include "../States/DogOwnedStates.h"
#include "../ObjectFactory/GameObject.h"
#include "../FSM/State.h"
#include "NeedsComponent.h"
#include "../ObjectFactory/ObjectFactory.h"
#include <glm/vec2.hpp>

struct Telegram;

class DogAIComponent : public NeedsComponent
{
public:
    DogAIComponent(GameObject *obj) : NeedsComponent(obj)
    {
        m_manager = std::make_shared<StateManager<DogAIComponent>>(this);
        m_manager->setCurrentState(LayDownAndRest::instance());
    }

    void update(GameObject *obj, float deltaTime) override;

    void init(tinyxml2::XMLNode *pNode) override;

    virtual void draw(Falcon::SpriteBatch &spriteBatch, float deltaTime);

    void handleMessage(const Telegram &telegram) override;

    void printMessage(const std::string &text)
    { m_text = text; }

    std::shared_ptr<StateManager<DogAIComponent>> getFSM()
    { return  m_manager; }

    void moveToTheHuman();


private:
    std::shared_ptr<StateManager<DogAIComponent>> m_manager;
    Falcon::SpriteFont *m_spriteFont;
    std::string m_text = "";
    glm::vec2 m_position;
    glm::vec2 m_direction;
    bool m_shouldMove = false;
};


#endif

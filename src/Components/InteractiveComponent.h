#ifndef SUNFLOWERSPANIEL_INTERACTIVECOMPONENT_H
#define SUNFLOWERSPANIEL_INTERACTIVECOMPONENT_H


#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include <Falcon/InputOutput/InputManager.h>
#include "Falcon/2D/SpriteFont/SpriteFont.h"
#include "Component.h"
#include "../ObjectFactory/GameObject.h"

class InteractiveComponent : public Component
{
public:
    InteractiveComponent(GameObject* obj) : Component(obj)
            {}
    void init(tinyxml2::XMLNode *pNode) override;

    void update(GameObject *obj, float /*deltaTime*/) override;

    virtual void draw(Falcon::SpriteBatch &spriteBatch, float /*deltaTime*/);

    void startContact()
    { m_visible = true; }

    void endContact()
    { m_visible = false; }

private:
    unsigned int m_interactionKeyID = 0;
    std::string m_interactionType;
    Falcon::SpriteFont *m_spriteFont;
    std::string m_text;
    glm::vec2 m_position;
    Falcon::Color m_color;
    float m_textScale;
    bool m_visible = false;
};


#endif

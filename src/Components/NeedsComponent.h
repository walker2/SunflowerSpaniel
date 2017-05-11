#ifndef SUNFLOWERSPANIEL_NEEDSCOMPONENT_H
#define SUNFLOWERSPANIEL_NEEDSCOMPONENT_H


#include "Component.h"

class NeedsComponent : public Component
{

public:
    NeedsComponent(GameObject *obj) : Component(obj)
    {}

    bool isThirsty()
    { return m_thirst > 1; }

    bool isHungry()
    { return m_hunger > 1; }

    bool isFatigued()
    { return m_fatigue > 1; }

    float getThirst()
    { return m_thirst; }

    float getHunger()
    { return m_hunger; }

    float getFatigue()
    { return m_fatigue; }

    void decreaseThirst(float amount)
    {
        if (m_thirst > 1) m_thirst = 1;
        m_thirst -= amount;
        if (m_thirst < 0) m_thirst = 0;
    }

    void decreaseHunger(float amount)
    {
        if (m_hunger > 1) m_hunger = 1;
        m_hunger -= amount;
        if (m_hunger < 0) m_hunger = 0;
    }

    void decreaseFatigue()
    { m_fatigue -= 0.0001f; }

    void increaseFatigue()
    { m_fatigue += 0.00001f; }

protected:
    float m_thirst = 0;
    float m_hunger = 0;
    float m_fatigue = 0;
};


#endif

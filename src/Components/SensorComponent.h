#ifndef SUNFLOWERSPANIEL_SENSORCOMPONENT_H
#define SUNFLOWERSPANIEL_SENSORCOMPONENT_H


#include "CollisionComponent.h"

class SensorComponent : public CollisionComponent
{
public:
    SensorComponent(GameObject* obj) : CollisionComponent(obj)
            {}
    void init(tinyxml2::XMLNode *pNode) override;

    void update(GameObject *obj, float deltaTime) override;
    void enable(bool enable)
    { m_isEnabled = enable; }

private:

    bool m_isEnabled = 0;
};


#endif

#ifndef SUNFLOWERSPANIEL_SENSORCOMPONENT_H
#define SUNFLOWERSPANIEL_SENSORCOMPONENT_H


#include "CollisionComponent.h"

class SensorComponent : public CollisionComponent
{
public:
    void init(tinyxml2::XMLNode *pNode) override;

    void update(GameObject *obj, float deltaTime) override;
};


#endif

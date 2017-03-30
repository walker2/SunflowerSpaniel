#ifndef SUNFLOWERSPANIEL_SPAWNOBJECTCOMPONENT_H
#define SUNFLOWERSPANIEL_SPAWNOBJECTCOMPONENT_H

#include "Component.h"
#include "../ObjectFactory/GameObject.h"

class SpawnObjectComponent : public Component
{
public:
    void update(GameObject *obj, float deltaTime) override;

    void init(tinyxml2::XMLNode *pNode) override;

    void receive(Message message) override;

private:
    void spawnObject();

private:
    glm::vec2 m_position;
    int m_number = 3;
};


#endif
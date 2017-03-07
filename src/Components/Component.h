#ifndef SUNFLOWERSPANIEL_COMPONENT_H
#define SUNFLOWERSPANIEL_COMPONENT_H

#include <TinyXML2/tinyxml2.h>
#include "../Messaging/Messages.h"

class GameObject;
class Component
{
public:
    Component()
    {}

    virtual void update(GameObject* obj, float deltaTime) = 0;
    virtual void init(tinyxml2::XMLNode* pNode) = 0;
    virtual void receive(Message /*message*/)
    {}

protected:
    GameObject* obj;
};


#endif

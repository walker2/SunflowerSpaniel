#ifndef SUNFLOWERSPANIEL_COMPONENT_H
#define SUNFLOWERSPANIEL_COMPONENT_H

#include <TinyXML2/tinyxml2.h>
#include <memory>
#include "../Messaging/Telegram.h"

class GameObject;

class Component
{
public:
    Component(GameObject *obj) : m_obj(obj)
    {}

    virtual void update(GameObject *obj, float deltaTime) = 0;

    virtual void init(tinyxml2::XMLNode *pNode) = 0;

    virtual void handleMessage(const Telegram & /*message*/)
    {}

    virtual void destroy()
    {}

    GameObject *getObject()
    { return m_obj; }

protected:
    GameObject *m_obj;
};


#endif

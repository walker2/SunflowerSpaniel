#ifndef SUNFLOWERSPANIEL_OBJECTFACTORY_H
#define SUNFLOWERSPANIEL_OBJECTFACTORY_H


#include <memory>
#include <TinyXML2/tinyxml2.h>
#include "GameObject.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "PlayerInputComponent.h"

class ObjectFactory
{
public:
    ObjectFactory();
    std::shared_ptr<GameObject> createObject(const char* objectResource);
    void addComponent(std::shared_ptr<GameObject> obj, tinyxml2::XMLNode* pNode);


    void setWorld(b2World* world) { m_world = world; };
private:
    unsigned long getNextActorId()
    {
        ++m_lastObjectID;
        return m_lastObjectID;
    }

    unsigned long m_lastObjectID;
    b2World* m_world;
};


#endif

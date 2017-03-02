#ifndef SUNFLOWERSPANIEL_OBJECTFACTORY_H
#define SUNFLOWERSPANIEL_OBJECTFACTORY_H


#include <memory>
#include <TinyXML2/tinyxml2.h>
#include "GameObject.h"
#include "../Components/CollisionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerInputComponent.h"

class ObjectFactory
{
public:
    static ObjectFactory& instance()
    {
        static ObjectFactory *instance = new ObjectFactory();
        return *instance;
    }

    std::shared_ptr<GameObject> createObject(const char* objectResource);
    void addComponent(std::shared_ptr<GameObject> obj, tinyxml2::XMLNode* pNode);
    void setWorld(b2World* world) { m_world = world; };
    std::vector<std::shared_ptr<GameObject>>* getGameObjects() { return &m_gameObjects; };
private:
    unsigned long getNextActorId()
    {
        ++m_lastObjectID;
        return m_lastObjectID;
    }

    unsigned long m_lastObjectID;
    b2World* m_world;

private:
    ObjectFactory() {};
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;
};


#endif

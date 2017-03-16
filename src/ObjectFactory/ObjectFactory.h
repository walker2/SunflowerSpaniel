#ifndef SUNFLOWERSPANIEL_OBJECTFACTORY_H
#define SUNFLOWERSPANIEL_OBJECTFACTORY_H


#include <memory>
#include <TinyXML2/tinyxml2.h>
#include "GameObject.h"
#include "../Components/CollisionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PlayerInputComponent.h"

/**
 * A class for creating new GameObjects from xml source
 */
class ObjectFactory
{
public:
    /**
     * Get's singletons instance of an object
     * @return Object Factory object
     */
    static ObjectFactory &instance()
    {
        static ObjectFactory *instance = new ObjectFactory();
        return *instance;
    }

    /**
     * Returns a new GameObject from filePath to the .xml file
     * @param objectResource filePath to the .xml file
     * @return a new GameObject
     */
    std::shared_ptr<GameObject> createObject(const char *objectResource);

    /**
     * Function that adds needed Component type from component name in XMLNode
     * @param obj GameObject we should attach Component to
     * @param pNode XMLNode that contains name of the Component
     */
    void addComponent(std::shared_ptr<GameObject> obj, tinyxml2::XMLNode *pNode);

    void setWorld(b2World *world)
    { m_world = world; }

    std::vector<std::shared_ptr<GameObject>> *getGameObjects()
    { return &m_gameObjects; }

    void deleteObject(GameObject* obj)
    {
        m_deletedGameObjects.push_back(obj);
    }

    void deleteGameObjects()
    {
        for (auto obj : m_deletedGameObjects)
        {
            obj->destroy();
        }
        m_deletedGameObjects.clear();
    }
private:
    unsigned long getNextActorId()
    {
        ++m_lastObjectID;
        return m_lastObjectID;
    }

    unsigned long m_lastObjectID;
    b2World *m_world;

private:
    ObjectFactory()
    {}
    std::vector<std::shared_ptr<GameObject>> m_gameObjects; ///< Vector of all gameObjects
    std::vector<GameObject*> m_deletedGameObjects;  ///< Vector of gameObjects that should be deleted on the next frame
};


#endif

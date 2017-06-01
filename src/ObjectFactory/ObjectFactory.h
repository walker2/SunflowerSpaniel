#ifndef SUNFLOWERSPANIEL_OBJECTFACTORY_H
#define SUNFLOWERSPANIEL_OBJECTFACTORY_H


#include <memory>
#include <TinyXML2/tinyxml2.h>
#include <Falcon/2D/Camera/Camera2D.h>
#include "GameObject.h"
#include "../Components/AnimationComponent.h"
#include "../Components/DirectionalAnimationComponent.h"
#include "../Components/SensorComponent.h"
#include "../Components/SpawnObjectComponent.h"
#include "../Components/PlayerInputComponent.h"
#include "../Components/InteractiveComponent.h"

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

    void drawGameObjects(Falcon::SpriteBatch &spriteBatch, float deltaTime,
                         Falcon::Camera2D &camera, Falcon::DebugRenderer &debugRender, bool renderDebug);

    void updateGameObjects(float deltaTime);

    void addObject(std::shared_ptr<GameObject> object);

    void deleteObject(GameObject *obj);

    void deleteGameObjects();

    void dispose()
    { m_gameObjectsMap.clear(); }

    long int getNumberOfGameObjects()
    { return m_gameObjectsMap.size(); }

    std::shared_ptr<GameObject> getObjectFromID(int id)
    {
        std::map<int, std::shared_ptr<GameObject>>::const_iterator ent = m_gameObjectsMap.find(id);

        assert ((ent != m_gameObjectsMap.end()) && "<EntityManager::GetEntityFromID>: invalid ID");

        return ent->second;
    }


    void setDogPlayerID(int id)
    { m_dogPlayerID = id; }

    void setHumanPlayerID(int id)
    { m_humanPlayerID = id; }

    void setCurrentPlayerID(int id)
    { m_currentPlayerID = id; }

    int getDogPlayerID()
    { return m_dogPlayerID; }

    int getHumanPlayerID()
    { return m_humanPlayerID; }

    int getCurrentPlayerID()
    { return m_currentPlayerID; }

private:
    unsigned long getNextObjectId()
    {
        ++m_lastObjectID;
        return m_lastObjectID;
    }

    unsigned long m_lastObjectID = 0;
    b2World *m_world;
    int m_dogPlayerID;
    int m_humanPlayerID;
    int m_currentPlayerID;

private:
    ObjectFactory()
    {
        //m_layerGameObjects.resize(100);
    }

    //std::vector<std::vector<std::shared_ptr<GameObject>>> m_layerGameObjects;   ///< Matrix for layered rendering
    std::map<int, std::shared_ptr<GameObject>> m_gameObjectsMap; ///< Map for fast lookup speeds for messaging
    std::vector<GameObject *> m_deletedGameObjects;  ///< Vector of gameObjects that should be deleted on the next frame
};


#endif

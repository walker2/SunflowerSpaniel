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
                         Falcon::Camera2D &camera, Falcon::DebugRenderer &debugRender, bool renderDebug)
    {
        for (unsigned long i = 0; i < m_layerGameObjects.size(); i++)
        {
            spriteBatch.begin();
            for (auto object : m_layerGameObjects[i])
            {
                auto spriteComponent = object->getComponent<SpriteComponent>();
                auto animationComponent = object->getComponent<AnimationComponent>();
                auto collisionComponent = object->getComponent<CollisionComponent>();
                auto bodyComponent = object->getComponent<BodyComponent>();
                auto sensorComponent = object->getComponent<SensorComponent>();
                auto interactiveComponent = object->getComponent<InteractiveComponent>();

                if (!collisionComponent)
                {
                    if (spriteComponent)
                    {
                        spriteComponent->draw(spriteBatch);
                    }

                    if (animationComponent)
                    {
                        animationComponent->draw(spriteBatch, deltaTime);
                    }
                } else if (camera.isBoxVisible(bodyComponent->getPosition(), collisionComponent->getDimensions()))
                {
                    if (spriteComponent)
                    {
                        spriteComponent->draw(spriteBatch);
                    }

                    if (animationComponent)
                    {
                        animationComponent->draw(spriteBatch, deltaTime);
                    }

                    if (interactiveComponent)
                    {
                        interactiveComponent->draw(spriteBatch, deltaTime);
                    }

                    if (renderDebug)
                    {
                        if (collisionComponent)
                        {
                            if (bodyComponent->getBody()->GetType() == b2_dynamicBody)
                            {
                                collisionComponent->drawDebug(debugRender, Falcon::Color(255, 0, 255, 255));
                            } else
                            {

                                collisionComponent->drawDebug(debugRender, Falcon::Color(255, 255, 0, 255));
                            }
                        }

                        if (sensorComponent)
                        {
                            sensorComponent->drawDebug(debugRender, Falcon::Color(0, 255, 0, 255));
                        }
                    }
                }
            }
            spriteBatch.end();
            spriteBatch.renderBatch();
        }
    }

    void updateGameObjects(float deltaTime)
    {
        for (unsigned long i = 0; i < m_layerGameObjects.size(); i++)
        {
            for (auto object : m_layerGameObjects[i])
            {
                if (!object->isDestroyed())
                {
                    object->update(deltaTime);
                }
            }
        }
    }

    void addObject(std::shared_ptr<GameObject> object)
    {
        switch (object->getLayer())
        {
            case 0:
                m_layerGameObjects[0].push_back(object);
                break;
            case 1:
                m_layerGameObjects[1].push_back(object);
                break;
            case 2:
                m_layerGameObjects[2].push_back(object);
                break;
            case 3:
                m_layerGameObjects[3].push_back(object);
                break;
            default:break;
        }
    }

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

    long int getNumberOfGameObjectsOnLayer(int layer)
    { return m_layerGameObjects[layer].size(); }

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
    {
        m_layerGameObjects.resize(4);
    }
    std::vector<std::vector<std::shared_ptr<GameObject>>> m_layerGameObjects;
    std::vector<GameObject*> m_deletedGameObjects;  ///< Vector of gameObjects that should be deleted on the next frame
};


#endif

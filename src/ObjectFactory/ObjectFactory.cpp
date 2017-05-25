#include "ObjectFactory.h"
#include "../Components/DogAIComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/HumanAIComponent.h"
#include "../Components/DialogueComponent.h"


std::shared_ptr<GameObject> ObjectFactory::createObject(const char *objectResource)
{
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult = xmlDoc.LoadFile(objectResource);
    if (eResult != tinyxml2::XMLError::XML_SUCCESS)
    {
        printf("Failed to create object. Error: %i\n", eResult);
        return std::shared_ptr<GameObject>();
    }
    auto nextObjectID = getNextObjectId();
    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(nextObjectID);

    tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr)
    {
        printf("Failed to find root. Error: %i\n", tinyxml2::XMLError::XML_ERROR_FILE_READ_ERROR);
        return std::shared_ptr<GameObject>();
    }

    for (tinyxml2::XMLNode *pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
    {
        addComponent(obj, pNode);
    }
    m_gameObjectsMap.emplace(obj->getID(), obj);
    return obj;
}

void ObjectFactory::addComponent(std::shared_ptr<GameObject> obj, tinyxml2::XMLNode *pNode)
{

    std::string component = pNode->Value();
    if (component == "NameComponent")
    {
        tinyxml2::XMLElement *pNameElement = pNode->FirstChildElement("Name");

        if (pNameElement)
        {
            obj->setName(pNameElement->GetText());
        }
    }
    if (component == "BodyComponent")
    {
        obj->attachComponent<BodyComponent>(obj.get());
        obj->getComponent<BodyComponent>()->setWorld(m_world);
        obj->getComponent<BodyComponent>()->init(pNode);
    } else if (component == "CollisionComponent")
    {
        obj->attachComponent<CollisionComponent>(obj.get());
        obj->getComponent<CollisionComponent>()->setObject(obj.get());
        obj->getComponent<CollisionComponent>()->init(pNode);
    } else if (component == "SpriteComponent")
    {
        obj->attachComponent<SpriteComponent>(obj.get());
        obj->getComponent<SpriteComponent>()->init(pNode);
    } else if (component == "PlayerInputComponent")
    {
        obj->attachComponent<PlayerInputComponent>(obj.get());
        obj->getComponent<PlayerInputComponent>()->init(pNode);
    } else if (component == "AnimationComponent")
    {
        obj->attachComponent<AnimationComponent>(obj.get());
        obj->getComponent<AnimationComponent>()->init(pNode);
    } else if (component == "DirectionalAnimationComponent")
    {
        obj->attachComponent<DirectionalAnimationComponent>(obj.get());
        obj->getComponent<DirectionalAnimationComponent>()->init(pNode);
    } else if (component == "SensorComponent")
    {
        obj->attachComponent<SensorComponent>(obj.get());
        obj->getComponent<SensorComponent>()->setObject(obj.get());
        obj->getComponent<SensorComponent>()->init(pNode);
    } else if (component == "InteractiveComponent")
    {
        obj->attachComponent<InteractiveComponent>(obj.get());
        obj->getComponent<InteractiveComponent>()->init(pNode);
    } else if (component == "SpawnObjectComponent")
    {
        obj->attachComponent<SpawnObjectComponent>(obj.get());
        obj->getComponent<SpawnObjectComponent>()->init(pNode);
    } else if (component == "DogAIComponent")
    {
        obj->attachComponent<DogAIComponent>(obj.get());
        obj->getComponent<DogAIComponent>()->init(pNode);
    } else if (component == "HumanAIComponent")
    {
        obj->attachComponent<HumanAIComponent>(obj.get());
        obj->getComponent<HumanAIComponent>()->init(pNode);
    } else if (component == "InventoryComponent")
    {
        obj->attachComponent<InventoryComponent>(obj.get());
        obj->getComponent<InventoryComponent>()->init(pNode);
    } else if (component == "DialogueComponent")
    {
        obj->attachComponent<DialogueComponent>(obj.get());
        obj->getComponent<DialogueComponent>()->init(pNode);
    }


}

void ObjectFactory::drawGameObjects(Falcon::SpriteBatch &spriteBatch, float deltaTime, Falcon::Camera2D &camera,
                                    Falcon::DebugRenderer &debugRender, bool renderDebug)
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
            auto dogAIComponent = object->getComponent<DogAIComponent>();
            auto humanAIComponent = object->getComponent<HumanAIComponent>();
            auto inventoryComponent = object->getComponent<InventoryComponent>();
            auto dialogueComponent = object->getComponent<DialogueComponent>();

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

                if (dogAIComponent)
                {
                    dogAIComponent->draw(spriteBatch, deltaTime);
                }

                if (humanAIComponent)
                {
                    humanAIComponent->draw(spriteBatch, deltaTime);
                }

                if (inventoryComponent)
                {
                    inventoryComponent->draw(spriteBatch, deltaTime);
                }

                if (dialogueComponent)
                {
                    dialogueComponent->draw();
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

void ObjectFactory::updateGameObjects(float deltaTime)
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

void ObjectFactory::addObject(std::shared_ptr<GameObject> object)
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

void ObjectFactory::deleteObject(GameObject *obj)
{
    m_deletedGameObjects.push_back(obj);
}

void ObjectFactory::deleteGameObjects()
{
    for (auto obj : m_deletedGameObjects)
    {
        obj->destroy();
    }
    m_deletedGameObjects.clear();
}

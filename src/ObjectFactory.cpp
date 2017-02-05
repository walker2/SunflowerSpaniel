#include "ObjectFactory.h"
#include <Falcon/Errors/Errors.h>


ObjectFactory::ObjectFactory()
{

}

std::shared_ptr<GameObject> ObjectFactory::createObject(const char *objectResource)
{
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult = xmlDoc.LoadFile(objectResource);
    if (eResult != tinyxml2::XMLError::XML_SUCCESS)
    {
        printf("Failed to create object. Error: %i\n", eResult);
        return std::shared_ptr<GameObject>();
    }
    auto nextObjectID = getNextActorId();
    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();

    tinyxml2::XMLNode *pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr)
    {
        printf("Failed to find root. Error: %i\n", tinyxml2::XMLError::XML_ERROR_FILE_READ_ERROR);
        return std::shared_ptr<GameObject>();
    }

    for (tinyxml2::XMLNode* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
    {
        addComponent(obj, pNode);
    }

    return obj;
}

void ObjectFactory::addComponent(std::shared_ptr<GameObject> obj, tinyxml2::XMLNode* pNode)
{

    std::string component = pNode->Value();
    if (component == "BodyComponent")
    {
        obj->attachComponent<BodyComponent>();
        obj->getComponent<BodyComponent>()->setWorld(m_world);
        obj->getComponent<BodyComponent>()->init(pNode);
    }
    else if (component == "CollisionComponent")
    {
        obj->attachComponent<CollisionComponent>();
        obj->getComponent<CollisionComponent>()->setObject(obj.get());
        obj->getComponent<CollisionComponent>()->init(pNode);
    }
    else if (component == "SpriteComponent")
    {
        obj->attachComponent<SpriteComponent>();
        obj->getComponent<SpriteComponent>()->init(pNode);
    }
    else if (component == "PlayerInputComponent")
    {
        obj->attachComponent<PlayerInputComponent>();
        obj->getComponent<PlayerInputComponent>()->init(pNode);
    }

}

#include "SpawnObjectComponent.h"
#include "../ObjectFactory/ObjectFactory.h"
#include "../Messaging/Messages.h"
#include <random>

void SpawnObjectComponent::update(GameObject *obj, float /*deltaTime*/)
{
    auto body = obj->getComponent<BodyComponent>()->getBody();
    m_position.x = body->GetPosition().x;
    m_position.y = body->GetPosition().y;
}

void SpawnObjectComponent::init(tinyxml2::XMLNode *pNode)
{
    tinyxml2::XMLElement *pTextureElement = pNode->FirstChildElement("Object");

    if (pTextureElement)
    {
        m_objectFilePath = pTextureElement->GetText();
    }
}

void SpawnObjectComponent::handleMessage(const Telegram &message)
{
    if (message.msg == Message::PLAYER_SPAWNS_NEW_OBJECT)
    {
        spawnObject();
    }
}

void SpawnObjectComponent::spawnObject()
{
    std::mt19937 rng(time(0));
    std::uniform_real_distribution<float> x_dist(2.5, 5.0f);
    std::uniform_real_distribution<float> y_dist(2.5, 5.0f);
    for (int i = 0; i < 5; i++)
    {
        auto circle = ObjectFactory::instance().createObject(m_objectFilePath.c_str());
        circle->getComponent<BodyComponent>()->setPosition(m_position + glm::vec2(x_dist(rng), y_dist(rng)));
        circle->setLayer(1);
        ObjectFactory::instance().addObject(circle);
    }
}


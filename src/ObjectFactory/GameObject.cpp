//
// Created by andrewshipilo on 2/1/17.
//

#include "GameObject.h"

GameObject::GameObject()
{
    attachComponent<BodyComponent>();
}

void GameObject::destroy()
{
    for (auto comp : m_components)
    {
        if (comp)
            comp->destroy();
    }

    m_components.clear();
    m_isDestroyed = true;
}

void GameObject::update(float deltaTime)
{
    for (auto &component : m_components)
    {
        component->update(this, deltaTime);
    }
}

void GameObject::send(Message message)
{
    for (auto &component : m_components)
    {
        component->receive(message);
    }
}
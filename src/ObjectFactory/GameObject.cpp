#include "GameObject.h"

GameObject::GameObject(int id)
{
    attachComponent<BodyComponent>(this);
    m_ID = id;
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

bool GameObject::handleMessage(const Telegram &msg)
{
    for (auto &component : m_components)
    {
        component->handleMessage(msg);
    }
    return true;
}
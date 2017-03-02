#ifndef SUNFLOWERSPANIEL_OBJECT_H
#define SUNFLOWERSPANIEL_OBJECT_H


#include <vector>
#include <memory>
#include "../Components/Component.h"
#include "../Components/BodyComponent.h"
#include "../Messaging/Messages.h"

enum class DIRECTION { NONE = 0, LEFT, RIGHT, UP, DOWN};

class GameObject
{
public:

    GameObject()
    {
        attachComponent<BodyComponent>();
    };


    virtual void update(float deltaTime)
    {
        for (auto& component : m_components)
        {
            component->update(this, deltaTime);
        }
    };

    template <class T>
    std::shared_ptr<T> attachComponent()
    {
        // Create new component
        std::shared_ptr<T> newComponent = std::make_shared<T>();

        // Check if we don't have component of this type
        for (auto& component : m_components)
        {
            if (std::dynamic_pointer_cast<T>(component))
            {
                component = newComponent;
                return newComponent;
            }
        }

        m_components.push_back(newComponent);

        return newComponent;
    }
    template <class T>
    std::shared_ptr<T> getComponent()
    {
        // Check if we don't have component of this type
        for (auto& component : m_components)
        {
            if (std::dynamic_pointer_cast<T>(component))
            {
                return std::dynamic_pointer_cast<T>(component);
            }
        }
        return nullptr;
    }

    void send(Message message)
    {
        for (auto& component : m_components)
        {
            component->receive(message);
        }
    }

    void destroy()
    {
        m_components.clear();
    }

    DIRECTION getDirection() const { return m_direction; };
    void setDirection(DIRECTION dir) { m_direction = dir; };

protected:
    std::vector<std::shared_ptr<Component>> m_components;
    DIRECTION m_direction = DIRECTION::NONE;

};



#endif //SUNFLOWERSPANIEL_OBJECT_H

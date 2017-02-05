#ifndef SUNFLOWERSPANIEL_OBJECT_H
#define SUNFLOWERSPANIEL_OBJECT_H


#include <vector>
#include <memory>
#include "Component.h"
#include "BodyComponent.h"

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


protected:
    std::vector<std::shared_ptr<Component>> m_components;
};



#endif //SUNFLOWERSPANIEL_OBJECT_H

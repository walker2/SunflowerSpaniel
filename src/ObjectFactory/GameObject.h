#ifndef SUNFLOWERSPANIEL_OBJECT_H
#define SUNFLOWERSPANIEL_OBJECT_H


#include <vector>
#include <memory>
#include "../Components/Component.h"
#include "../Components/BodyComponent.h"
#include "../Messaging/Telegram.h"

enum class DIRECTION
{
    NONE = 0, LEFT, RIGHT, UP, DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN
};

/**
 * Class that contains a bunch of components. Can add them and update
 */
class GameObject
{
public:
    /**
     * Default constructor: attaches default BodyComponent
     */
    GameObject(int id);

    /**
     * Clears all components
     */
    void destroy();

    /**
     * Method that iterates through all components and updates them with deltaTime
     * @param deltaTime time that have passed since the last frame
     */
    virtual void update(float deltaTime);

    /**
     * Method for attaching components to the GameObject
     * @tparam T Component type
     * @return shared pointer to created or existing component
     */
    template<class T>
    std::shared_ptr<T> attachComponent(GameObject *obj)
    {
        // Create new component
        std::shared_ptr<T> newComponent = std::make_shared<T>(obj);

        // Check if we don't have component of this type
        for (auto &component : m_components)
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

    /**
     * Method for getting component by type
     * @tparam T Component type
     * @return shared pointer to existing component or nullptr if there's none
     */
    template<class T>
    std::shared_ptr<T> getComponent()
    {
        // Check if we don't have component of this type
        for (auto &component : m_components)
        {
            if (std::dynamic_pointer_cast<T>(component))
            {
                return std::dynamic_pointer_cast<T>(component);
            }
        }
        return nullptr;
    }

    /**
     * Sends some message to all component within this gameObject
     * @param message message
     */
    bool handleMessage(const Telegram &msg);

    DIRECTION getDirection() const
    { return m_direction; }

    int getLayer()
    { return m_layer; }

    int getID()
    { return m_ID; }

    std::string getName()
    { return m_name; }


    void setDirection(DIRECTION dir)
    { m_direction = dir; }

    void setLayer(int num)
    { m_layer = num; }

    void setName(const std::string &name)
    { m_name = name; }

    bool isDestroyed()
    { return m_isDestroyed; }

protected:
    std::vector<std::shared_ptr<Component>> m_components;   ///< A vector of all pointer to components that attached to this GameObject
    DIRECTION m_direction = DIRECTION::NONE;    ///< Direction gameObject is facing
    bool m_isDestroyed = false;
    int m_layer = 0;
    int m_ID;
    std::string m_name;

};


#endif

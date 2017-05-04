#ifndef SUNFLOWERSPANIEL_INVENTORYCOMPONENT_H
#define SUNFLOWERSPANIEL_INVENTORYCOMPONENT_H


#include <memory>
#include <map>
#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include "../ObjectFactory/GameObject.h"
#include "../FSM/StateManager.h"
#include "../Messaging/Messages.h"
#include "../ObjectFactory/ObjectFactory.h"

class InventoryComponent : public Component
{

public:
    InventoryComponent(GameObject* obj) : Component(obj)
    {}


    void init(tinyxml2::XMLNode *pNode) override
    {

    }

    void update(GameObject *obj, float deltaTime) override
    {

    }

    void draw(Falcon::SpriteBatch &spriteBatch, float deltaTime)
    {
    }

    void handleMessage(const Telegram &telegram) override
    {
        if (telegram.msg == Message::PLAYER_PICK_UPS_OBJECT && telegram.receiver == this->getObject()->getID())
        {
            addItem(ObjectFactory::instance().getObjectFromID(telegram.sender)->getName());
        }
    }

    void addItem(std::string itemID)
    {
        auto newItem = m_items.find(itemID);
        if (newItem != m_items.end())
        {
          newItem->second += 1;
        }
        else
        {
            m_items.emplace(std::pair<std::string, int>(itemID, 1));
        }
    }

    void removeItem(std::string itemID)
    {
        auto newItem = m_items.find(itemID);
        if (newItem != m_items.end())
        {
            if (newItem->second > 1)
            {
                newItem->second -= 1;
            }
            else
            {
                m_items.erase(itemID);
            }
        }
    }

    std::map<std::string, int>& getItems()
    { return m_items; }

private:
    std::map<std::string, int> m_items;
};


#endif

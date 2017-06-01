#include "InventoryComponent.h"

void InventoryComponent::handleMessage(const Telegram &telegram)
{
    if (telegram.msg == Message::PLAYER_PICK_UPS_OBJECT && telegram.receiver == this->getObject()->getID())
    {
        addItem(ObjectFactory::instance().getObjectFromID(telegram.sender)->getName());
    }
}

void InventoryComponent::addItem(std::string itemID)
{
    auto newItem = m_items.find(itemID);
    if (newItem != m_items.end())
    {
        newItem->second += 1;
    } else
    {
        m_items.emplace(std::pair<std::string, int>(itemID, 1));
    }
}

void InventoryComponent::removeItem(std::string itemID)
{
    auto newItem = m_items.find(itemID);
    if (newItem != m_items.end())
    {
        if (newItem->second > 1)
        {
            newItem->second -= 1;
        } else
        {
            m_items.erase(itemID);
        }
    }
}

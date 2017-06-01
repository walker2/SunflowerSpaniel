//
// Created by walker2 on 4/20/17.
//

#include "MessageManager.h"
#include "../ObjectFactory/ObjectFactory.h"

void MessageManager::dispatchMsg(double delay, int sender, int receiver, int msg, void *extraInfo)
{
    auto pReceiver = ObjectFactory::instance().getObjectFromID(receiver);

    // Make sure that receiver is valid

    if (pReceiver == nullptr)
    {
        printf("Receiver does not exist");
        return;
    }

    // Create a telegram

    Telegram telegram(0, sender, receiver, msg, extraInfo);

    if (delay <= 0.0)
    {
        //send the telegram to the recipient
        discharge(pReceiver, telegram);
    } else
    {
        //TODO: Should be implemented

    }

}

void MessageManager::dispatchDelayedMessages()
{
    //TODO: Should be implemented
}

void MessageManager::discharge(std::shared_ptr<GameObject> receiver, const Telegram &msg)
{
    if (!(receiver->handleMessage(msg)))
    {
        printf("Message can't be send");
    }
}

#ifndef SUNFLOWERSPANIEL_MESSAGEMANAGER_H
#define SUNFLOWERSPANIEL_MESSAGEMANAGER_H

#include <set>
#include "Telegram.h"
#include "../ObjectFactory/GameObject.h"

//#define Dispatcher MessageManager::instance()

const double SEND_MSG_IMMEDIATELY = 0.0;
const int NO_ADDITIONAL_INFO = 0;
const int SENDER_ID_IRRELEVANT = -1;

class MessageManager
{
public:
    static MessageManager &instance()
    {
        static MessageManager *instance = new MessageManager();
        return *instance;
    };

    /// Send a message to another object. Receiving object is referenced by ID.
    void dispatchMsg(double delay,
                     int sender,
                     int receiver,
                     int msg,
                     void *extraInfo);

    /// Send out any delayed messages. This method should be called each time through the main game loop.
    void dispatchDelayedMessages();


private:
    /// Messages are sorted by their dispatch time.
    std::set<Telegram> m_priorityQ;

    MessageManager()
    {}

    void discharge(std::shared_ptr<GameObject> pReceiver, const Telegram &msg);

    MessageManager(const MessageManager &);

    MessageManager &operator=(const MessageManager &);

};


#endif
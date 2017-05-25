#ifndef SUNFLOWERSPANIEL_TELEGRAM_H
#define SUNFLOWERSPANIEL_TELEGRAM_H


#include <glm/glm.hpp>
#include <iostream>

struct Telegram
{
    /** Messages can be dispatched immediately or delayed for a specified amount of time.
    If a delay is necessary this field is stamped with the time the message should be dispatched.**/
    double dispatchTime;

    /// ID of object who sent this telegram
    int sender;

    /// ID of object who should recieve this telegram
    int receiver;

    /// ID of the message, that should be dispatched
    /// They are all enumerated in file Messages.h
    int msg;

    /// any additional information that may accompany the message
    void *extraInfo;

    Telegram() : dispatchTime(-1),
                 sender(-1),
                 receiver(-1),
                 msg(-1)
    {}


    Telegram(double time,
             int sender,
             int receiver,
             int msg,
             void *info = NULL) : dispatchTime(time),
                                  sender(sender),
                                  receiver(receiver),
                                  msg(msg),
                                  extraInfo(info)
    {}
};


/// Telegrams would be store in a priority queue. Therefore operator > should be overloaded
/// Note how the times must be smaller than smallestDelay apart before two Telegrams are considered unique.
const double smallestDelay = 0.25;

inline bool operator==(const Telegram &t1, const Telegram &t2)
{
    return (fabs(t1.dispatchTime - t2.dispatchTime) < smallestDelay) &&
           (t1.sender == t2.sender) &&
           (t1.receiver == t2.receiver) &&
           (t1.msg == t2.msg);
}

inline bool operator<(const Telegram &t1, const Telegram &t2)
{
    if (t1 == t2)
    {
        return false;
    } else
    {
        return (t1.dispatchTime < t2.dispatchTime);
    }
}

inline std::ostream &operator<<(std::ostream &os, const Telegram &t)
{
    os << "time: " << t.dispatchTime << "  Sender: " << t.sender
       << "   Receiver: " << t.receiver << "   Msg: " << t.msg;

    return os;
}

//handy helper function for dereferencing the ExtraInfo field of the Telegram
//to the required type.
template<class T>
inline T dereferenceToType(void *p)
{
    return *(T *) (p);
}


#endif


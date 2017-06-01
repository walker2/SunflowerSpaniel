#include "HumanOwnedStates.h"
#include "../Components/HumanAIComponent.h"

// SLEEP METHODS
void Sleep::enter(HumanAIComponent */*object*/)
{

}

void Sleep::execute(HumanAIComponent *object)
{
    if (object->getFatigue() <= 0.0f)
    {
        object->printMessage("What a terrible day to have nothing to eat");
        object->getFSM()->changeState(Hunt::instance());
    } else
    {
        object->decreaseFatigue();
        object->printMessage("Nightmares are better than life");
    }
}

void Sleep::exit(HumanAIComponent */*object*/)
{

}

bool Sleep::onMessage(HumanAIComponent */*object*/, const Telegram &/*telegram*/)
{
    return true;
}


// HUNT METHODS
void Hunt::enter(HumanAIComponent */*object*/)
{

}

void Hunt::execute(HumanAIComponent *object)
{
    object->increaseFatigue();
    object->printMessage("...");

    if (object->isThirsty())
    {
        object->printMessage("Kinda thirsty");
        //CHANGE STATE
    }

    if (object->isHungry())
    {
        object->printMessage("Stomach is grumbling about");
        //CHANGE STATE
    }
    if (object->isFatigued())
    {
        object->printMessage("What a beautiful time to sleep");
        object->getFSM()->changeState(Sleep::instance());
    }
}

void Hunt::exit(HumanAIComponent */*object*/)
{

}

bool Hunt::onMessage(HumanAIComponent */*object*/, const Telegram &/*telegram*/)
{
    return true;
}


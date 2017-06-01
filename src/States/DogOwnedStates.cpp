#include "DogOwnedStates.h"
#include "../Components/DogAIComponent.h"

// LAYDOWN METHODS
void LayDownAndRest::enter(DogAIComponent */*object*/)
{

}

void LayDownAndRest::execute(DogAIComponent *object)
{
    if (object->getFatigue() <= 0.0f)
    {
        object->printMessage("Is ready for a good hunt");
        object->getFSM()->changeState(SniffOutThePrey::instance());
    } else
    {
        object->decreaseFatigue();
        object->printMessage("Dreams about sheeps");
    }
}

void LayDownAndRest::exit(DogAIComponent */*object*/)
{

}

bool LayDownAndRest::onMessage(DogAIComponent */*object*/, const Telegram &/*telegram*/)
{
    return true;
}


// SNIFFOUTTHEPREY METHODS
void SniffOutThePrey::enter(DogAIComponent */*object*/)
{

}

void SniffOutThePrey::execute(DogAIComponent *object)
{
    object->increaseFatigue();
    object->printMessage("Scouting the area");
    object->moveToTheHuman();

    if (object->isThirsty())
    {
        object->printMessage("Wants to drink");
        //CHANGE STATE
    }

    if (object->isHungry())
    {
        object->printMessage("Wants to eat");
        //CHANGE STATE
    }
    if (object->isFatigued())
    {
        object->printMessage("Lays down to sleep");
        object->getFSM()->changeState(LayDownAndRest::instance());
    }
}

void SniffOutThePrey::exit(DogAIComponent */*object*/)
{

}

bool SniffOutThePrey::onMessage(DogAIComponent */*object*/, const Telegram &/*telegram*/)
{
    return true;
}

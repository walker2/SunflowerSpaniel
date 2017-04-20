#include "DogOwnedStates.h"
#include "../Components/DogAIComponent.h"

// LAYDOWN METHODS
void LayDownAndRest::enter(DogAIComponent *object)
{

}

void LayDownAndRest::execute(DogAIComponent *object)
{
    if (object->getFatigue() <= 0.0f)
    {
        object->printMessage("*** DOG IS READY FOR A GOOD HUNT ***");
        object->getFSM()->changeState(SniffOutThePrey::instance());
    } else
    {
        object->decreaseFatigue();
        object->printMessage("*** DREAMS ABOUT SHEEPS ***");
    }
}

void LayDownAndRest::exit(DogAIComponent *object)
{

}

bool LayDownAndRest::onMessage(DogAIComponent *object, const Telegram &telegram)
{
    return true;
}


// SNIFFOUTTHEPREY METHODS
void SniffOutThePrey::enter(DogAIComponent *object)
{

}

void SniffOutThePrey::execute(DogAIComponent *object)
{
    object->increaseFatigue();
    object->printMessage("*** DOG IS SEEKING FOR A NEW PREY ***");

    if(object->isThirsty())
    {
        object->printMessage("*** DOG WANTS TO DRINK ***");
        //CHANGE STATE
    }

    if(object->isHungry())
    {
        object->printMessage("*** DOG WANTS TO EAT ***");
        //CHANGE STATE
    }
    if(object->isFatigued())
    {
        object->printMessage("*** DOG LAYS DOWN TO SLEEP ***");
        object->getFSM()->changeState(LayDownAndRest::instance());
    }
}

void SniffOutThePrey::exit(DogAIComponent *object)
{

}

bool SniffOutThePrey::onMessage(DogAIComponent *object, const Telegram &telegram)
{
    return true;
}

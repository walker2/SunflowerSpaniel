#ifndef SUNFLOWERSPANIEL_CONTACTLISTENER_H
#define SUNFLOWERSPANIEL_CONTACTLISTENER_H


#include <Box2D/Box2D.h>
#include "../ObjectFactory/GameObject.h"
#include "../Components/InteractiveComponent.h"

/**
 * This class extends ContactListener class from Box2D library
 * Made for custom behaviour on physics collision
 */
class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact *contact)
    {
        GameObject *sensorObject = nullptr;
        GameObject *collideObject = nullptr;
        if (getSensorAndCollide(contact, sensorObject, collideObject) && (collideObject != nullptr))
        {
            auto interactiveComponent = collideObject->getComponent<InteractiveComponent>();

            if (interactiveComponent)
            {
                collideObject->getComponent<InteractiveComponent>()->startContact();
            }
        }

    }

    void EndContact(b2Contact *contact)
    {
        GameObject *sensorObject = nullptr;
        GameObject *collideObject = nullptr;
        if (getSensorAndCollide(contact, sensorObject, collideObject) && (collideObject != nullptr))
        {
            auto interactiveComponent = collideObject->getComponent<InteractiveComponent>();

            if (interactiveComponent)
            {
                collideObject->getComponent<InteractiveComponent>()->endContact();
            }
        }
    }

private:
    bool getSensorAndCollide(b2Contact *contact, GameObject *&sensorEntity, GameObject *&collideEntity)
    {
        b2Fixture *fixtureA = contact->GetFixtureA();
        b2Fixture *fixtureB = contact->GetFixtureB();

        //make sure only one of the fixtures was a sensor
        bool sensorA = fixtureA->IsSensor();
        bool sensorB = fixtureB->IsSensor();
        if (!(sensorA ^ sensorB))
            return false;

        GameObject *entityA = static_cast<GameObject *>(fixtureA->GetBody()->GetUserData());
        GameObject *entityB = static_cast<GameObject *>(fixtureB->GetBody()->GetUserData());

        if (sensorA)
        { //fixtureB must be an enemy aircraft
            sensorEntity = entityA;
            collideEntity = entityB;
        } else
        { //fixtureA must be an enemy aircraft
            sensorEntity = entityB;
            collideEntity = entityA;
        }
        return true;
    }

};


#endif

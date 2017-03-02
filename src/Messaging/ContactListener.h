#ifndef SUNFLOWERSPANIEL_CONTACTLISTENER_H
#define SUNFLOWERSPANIEL_CONTACTLISTENER_H


#include <Box2D/Box2D.h>
#include "../ObjectFactory/GameObject.h"
#include "../Components/InteractiveComponent.h"

class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact)
    {
        GameObject* sensorObject;
        GameObject* collideObject;
        if (getSensorAndCollide(contact, sensorObject, collideObject))
        {
            auto interactiveComponent = collideObject->getComponent<InteractiveComponent>();

            if (interactiveComponent)
            {
                collideObject->getComponent<InteractiveComponent>()->startContact();
            }
        }

    }

    void EndContact(b2Contact* contact)
    {
        GameObject* sensorObject;
        GameObject* collideObject;
        if (getSensorAndCollide(contact, sensorObject, collideObject))
        {
            auto interactiveComponent = collideObject->getComponent<InteractiveComponent>();

            if (interactiveComponent)
            {
                collideObject->getComponent<InteractiveComponent>()->endContact();
            }
        }
    }

private:
    bool getSensorAndCollide(b2Contact* contact, GameObject*& radarEntity, GameObject*& aircraftEntity)
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        //make sure only one of the fixtures was a sensor
        bool sensorA = fixtureA->IsSensor();
        bool sensorB = fixtureB->IsSensor();
        if (!(sensorA ^ sensorB))
            return false;

        GameObject* entityA = static_cast<GameObject*>(fixtureA->GetBody()->GetUserData());
        GameObject* entityB = static_cast<GameObject*>(fixtureB->GetBody()->GetUserData());

        if (sensorA)
        { //fixtureB must be an enemy aircraft
            radarEntity = entityA;
            aircraftEntity = entityB;
        }
        else
        { //fixtureA must be an enemy aircraft
            radarEntity = entityB;
            aircraftEntity = entityA;
        }
        return true;
    }

};


#endif

#ifndef SUNFLOWERSPANIEL_PLAYERINPUTCOMPONENT_H
#define SUNFLOWERSPANIEL_PLAYERINPUTCOMPONENT_H


#include <Falcon/InputOutput/InputManager.h>
#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include "Component.h"
#include "BodyComponent.h"
#include "GameObject.h"

class PlayerInputComponent : public Component
{
public:
    enum class DIRECTION { LEFT = 0, RIGHT, UP, DOWN};

    PlayerInputComponent() {};

    void init(tinyxml2::XMLNode *pNode) override
    {

    }

    void init(Falcon::InputManager* inputManager)
    {
        m_inputManager = inputManager;
    }
    void update(GameObject* obj, float deltaTime)
    {
        b2Body* body = obj->getComponent<BodyComponent>()->getBody();
        b2Vec2 movementSpeed(0.0f, 0.0f);

        if (m_inputManager->isKeyDown(SDLK_a))
        {
            movementSpeed.x += -1;
            m_direction = DIRECTION::LEFT;

        }
        else if (m_inputManager->isKeyDown(SDLK_d))
        {
            movementSpeed.x += 1;
            m_direction = DIRECTION::RIGHT;
        }

        if (m_inputManager->isKeyDown(SDLK_w))
        {
            movementSpeed.y += 1;
            m_direction = DIRECTION::UP;
        }
        else if (m_inputManager->isKeyDown(SDLK_s))
        {
            movementSpeed.y += -1 ;
            m_direction = DIRECTION::DOWN;
        }

        float length = movementSpeed.Length();
        if (length != 0)
        {
            movementSpeed.x /= length;
            movementSpeed.y /= length;
        }
        movementSpeed *= m_movementSpeed * deltaTime;
        body->SetLinearVelocity(movementSpeed);
        body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.7f,
                                       body->GetLinearVelocity().y * 0.7f));
    }
private:
    float m_movementSpeed = 20.0f;
    Falcon::InputManager* m_inputManager;
    DIRECTION m_direction = DIRECTION::LEFT;
};


#endif

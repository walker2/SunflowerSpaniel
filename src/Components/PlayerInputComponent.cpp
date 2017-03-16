//
// Created by andrewshipilo on 2/3/17.
//

#include <iostream>
#include "PlayerInputComponent.h"

void PlayerInputComponent::init(tinyxml2::XMLNode *pNode)
{
    tinyxml2::XMLElement *pSpeedElement = pNode->FirstChildElement("MovementSpeed");

    if (pSpeedElement)
    {
        pSpeedElement->QueryFloatText(&m_movementSpeed);
    }

    tinyxml2::XMLElement *pLeftKey = pNode->FirstChildElement("LeftKeyID");
    if (pLeftKey)
    {
        m_leftKeyID = static_cast<unsigned>(SDL_GetKeyFromName(pLeftKey->GetText()));
    }

    tinyxml2::XMLElement *pRightKey = pNode->FirstChildElement("RightKeyID");
    if (pRightKey)
    {
        m_rightKeyID = static_cast<unsigned>(SDL_GetKeyFromName(pRightKey->GetText()));
    }

    tinyxml2::XMLElement *pUpKey = pNode->FirstChildElement("UpKeyID");
    if (pUpKey)
    {
        m_upKeyID = static_cast<unsigned>(SDL_GetKeyFromName(pUpKey->GetText()));
    }

    tinyxml2::XMLElement *pDownKey = pNode->FirstChildElement("DownKeyID");
    if (pDownKey)
    {
        m_downKeyID = static_cast<unsigned>(SDL_GetKeyFromName(pDownKey->GetText()));
    }
}

void PlayerInputComponent::update(GameObject *obj, float deltaTime)
{
    b2Body *body = obj->getComponent<BodyComponent>()->getBody();
    b2Vec2 movementSpeed(0.0f, 0.0f);

    if (Falcon::InputManager::instance().isKeyDown(m_leftKeyID))
    {
        movementSpeed.x += -1;

        if (obj->getDirection() == DIRECTION::DOWN)
        {
            obj->setDirection(DIRECTION::LEFT_DOWN);
            return;
        } else if (obj->getDirection() == DIRECTION::UP)
        {
            obj->setDirection(DIRECTION::LEFT_UP);
            return;
        } else
        {
            obj->setDirection(DIRECTION::LEFT);
        }

    } else if (Falcon::InputManager::instance().isKeyDown(m_rightKeyID))
    {
        movementSpeed.x += 1;
        if (obj->getDirection() == DIRECTION::DOWN)
        {
            obj->setDirection(DIRECTION::RIGHT_DOWN);
            return;
        } else if (obj->getDirection() == DIRECTION::UP)
        {
            obj->setDirection(DIRECTION::RIGHT_UP);
            return;
        } else
        {
            obj->setDirection(DIRECTION::RIGHT);
        }
    }

    if (Falcon::InputManager::instance().isKeyDown(m_upKeyID))
    {
        movementSpeed.y += 1;

        if (obj->getDirection() == DIRECTION::LEFT)
        {
            obj->setDirection(DIRECTION::LEFT_UP);
        } else if (obj->getDirection() == DIRECTION::RIGHT)
        {
            obj->setDirection(DIRECTION::RIGHT_UP);
        } else
        {
            obj->setDirection(DIRECTION::UP);
        }
    } else if (Falcon::InputManager::instance().isKeyDown(m_downKeyID))
    {
        movementSpeed.y += -1;
        if (obj->getDirection() == DIRECTION::LEFT)
        {
            obj->setDirection(DIRECTION::LEFT_DOWN);
        } else if (obj->getDirection() == DIRECTION::RIGHT)
        {
            obj->setDirection(DIRECTION::RIGHT_DOWN);
        } else
        {
            obj->setDirection(DIRECTION::DOWN);
        }
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

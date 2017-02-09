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
    PlayerInputComponent() {};

    void init(tinyxml2::XMLNode *pNode) override;

    void update(GameObject* obj, float deltaTime);

private:
    float m_movementSpeed = 20.0f;
    unsigned int m_leftKeyID = 0;
    unsigned int m_rightKeyID = 0;
    unsigned int m_upKeyID = 0;
    unsigned int m_downKeyID = 0;

};


#endif

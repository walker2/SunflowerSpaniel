#ifndef SUNFLOWERSPANIEL_DIRECTIONALANIMATIONCOMPONENT_H
#define SUNFLOWERSPANIEL_DIRECTIONALANIMATIONCOMPONENT_H


#include "AnimationComponent.h"

class DirectionalAnimationComponent : public AnimationComponent
{
public:
    DirectionalAnimationComponent(GameObject *obj) : AnimationComponent(obj)
    {}

    void draw(Falcon::SpriteBatch &spriteBatch, float deltaTime) override;

    void init(tinyxml2::XMLNode *pNode) override;

private:
    int m_tileIndexLeftDir = -1;
    int m_tileIndexRightDir = -1;
    int m_tileIndexUpDir = -1;
    int m_tileIndexDownDir = -1;
    int m_tileIndexLeftUpDir = -1;
    int m_tileIndexLeftDownDir = -1;
    int m_tileIndexRightUpDir = -1;
    int m_tileIndexRightDownDir = -1;
};


#endif

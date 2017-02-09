#ifndef SUNFLOWERSPANIEL_DIRECTIONALANIMATIONCOMPONENT_H
#define SUNFLOWERSPANIEL_DIRECTIONALANIMATIONCOMPONENT_H


#include "AnimationComponent.h"

class DirectionalAnimationComponent : public AnimationComponent
{
public:
    void draw(Falcon::SpriteBatch &spriteBatch, float deltaTime) override;

    void init(tinyxml2::XMLNode *pNode) override;

private:
    int m_tileIndexLeftDir = -1;
    int m_tileIndexRightDir = -1;
    int m_tileIndexUpDir = -1;
    int m_tileIndexDownDir = -1;
};


#endif

#ifndef SUNFLOWERSPANIEL_ANIMATIONCOMPONENT_H
#define SUNFLOWERSPANIEL_ANIMATIONCOMPONENT_H


#include "Component.h"
#include "SpriteComponent.h"

class AnimationComponent : public Component
{
public:
    AnimationComponent(GameObject *obj) : Component(obj)
    {}

    void init(tinyxml2::XMLNode *pNode) override;

    void update(GameObject *obj, float deltaTime) override;

    virtual void draw(Falcon::SpriteBatch &spriteBatch, float deltaTime);

    void setTileSheet(const std::string &filePath);

protected:
    float m_animSpeed = 0.0f;
    float m_animTime = 0.0f;
    int m_frameCount = 1;

    DIRECTION m_direction = DIRECTION::NONE;
    b2Body *m_body = nullptr;
    Falcon::TileSheet m_tileSheet;
    glm::vec4 m_destRect;
    glm::vec2 m_spriteDims;
    glm::vec2 m_spritePos;
    Falcon::Color m_color;
    int m_tileIndex = -1;
    float m_angle;
    float m_tileSize = 32;
};


#endif

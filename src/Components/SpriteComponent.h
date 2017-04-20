#ifndef SUNFLOWERSPANIEL_TEXTURECOMPONENT_H
#define SUNFLOWERSPANIEL_TEXTURECOMPONENT_H

#include <Falcon/2D/Sprite.h>
#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include <Falcon/2D/TileSheet.h>
#include <Falcon/ResourceManager/ResourceManager.h>
#include "Component.h"
#include "../ObjectFactory/GameObject.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent(GameObject* obj) : Component(obj)
    {}

    void init(tinyxml2::XMLNode *pNode) override;

    void init(const std::string &filePath,
              Falcon::Color color,
              const glm::vec2 dimensions,
              const glm::vec2 spritePosition,
              int spriteID = 0);

    void update(GameObject *obj, float deltaTime);

    void draw(Falcon::SpriteBatch &spriteBatch);


    // Getters
    int getTileIndex()
    { return m_tileIndex; }

    glm::vec2 getDimensions()
    { return m_spriteDims; }

    // Setters
    void setTileSheet(const std::string &filePath);

    void setTileIndex(int tileIndex)
    { m_tileIndex = tileIndex; }


protected:
    Falcon::TileSheet m_tileSheet;
    glm::vec4 m_destRect;
    glm::vec2 m_spriteDims;
    glm::vec2 m_spritePos;
    Falcon::Color m_color;
    int m_tileIndex = 0;
    float m_angle;
    float m_tileSize = 32;

};


#endif

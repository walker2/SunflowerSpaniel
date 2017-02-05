#ifndef SUNFLOWERSPANIEL_TEXTURECOMPONENT_H
#define SUNFLOWERSPANIEL_TEXTURECOMPONENT_H

#include <Falcon/2D/Sprite.h>
#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include <Falcon/2D/TileSheet.h>
#include <Falcon/ResourceManager/ResourceManager.h>
#include "Component.h"
#include "GameObject.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent() {};

    void init(tinyxml2::XMLNode *pNode) override
    {
        tinyxml2::XMLElement *pTextureElement = pNode->FirstChildElement("Texture");

        if (pTextureElement)
        {
            std::string filePath = pTextureElement->GetText();
            setTileSheet(filePath);
        }

        tinyxml2::XMLElement *pColorElement = pNode->FirstChildElement("Color");
        int r = 0;
        int g = 0;
        int b = 0;
        int a = 0;
        if (pColorElement)
        {
            pColorElement->QueryIntAttribute("r", &r);
            pColorElement->QueryIntAttribute("g", &g);
            pColorElement->QueryIntAttribute("b", &b);
            pColorElement->QueryIntAttribute("a", &a);
            Falcon::Color color(r, g, b, a);
            m_color = color;
        }

        tinyxml2::XMLElement *pDimensionsElement = pNode->FirstChildElement("Dimensions");
        float height = 0;
        float width = 0;

        if (pDimensionsElement)
        {
            pDimensionsElement->QueryFloatAttribute("height", &height);
            pDimensionsElement->QueryFloatAttribute("width", &width);
            m_spriteDims.x = width;
            m_spriteDims.y = height;
        }

        tinyxml2::XMLElement *pPositionElement = pNode->FirstChildElement("Position");
        float x = 0.0f;
        float y = 0.0f;

        if (pPositionElement)
        {
            pPositionElement->QueryFloatAttribute("x", &x);
            pPositionElement->QueryFloatAttribute("y", &y);
        }
        m_spritePos.x = x;
        m_spritePos.y = y;

        tinyxml2::XMLElement *pSpriteIDElement = pNode->FirstChildElement("SpriteID");

        if (pSpriteIDElement)
        {
            pSpriteIDElement->QueryIntText(&m_tileIndex);
        }
    }

    void init(const std::string& filePath,
              Falcon::Color color,
              const glm::vec2 dimensions,
              const glm::vec2 spritePosition,
              int spriteID = 0)
    {
        setTileSheet(filePath);
        m_tileIndex = spriteID;
        m_color = color;
        m_spriteDims = dimensions;
        m_spritePos = spritePosition;
    }
    void update(GameObject* obj, float deltaTime)
    {
        auto body = obj->getComponent<BodyComponent>()->getBody();
        m_destRect.x = (body->GetPosition().x - m_spriteDims.x / 2.0f) + m_spritePos.x;
        m_destRect.y = (body->GetPosition().y - m_spriteDims.y / 2.0f) + m_spritePos.y;
        m_destRect.z = m_spriteDims.x;
        m_destRect.w = m_spriteDims.y;
        m_angle = body->GetAngle();
    }

    void draw(Falcon::SpriteBatch& spriteBatch)
    {
        if (m_tileIndex)
        {
            spriteBatch.draw(m_destRect, m_tileSheet.getUVs(m_tileIndex), m_tileSheet.texture.id, 0.0f,
                             Falcon::Color(255, 255, 225, 255), m_angle);
        }
        else
        {
            glm::vec4 uvRect(0.0, 0.0, 1.0, 1.0);
            spriteBatch.draw(m_destRect, uvRect, m_tileSheet.texture.id, 0.0f, m_color, m_angle);
        }
    };

    void setTileSheet(const std::string& filePath)
    {
        Falcon::GLTexture texture = Falcon::ResourceManager::getTexture(filePath);
        m_tileSheet.init(texture, glm::ivec2(texture.width / 32, texture.height / 32));
    };



private:
    Falcon::TileSheet m_tileSheet;
    glm::vec4 m_destRect;
    glm::vec2 m_spriteDims;
    glm::vec2 m_spritePos;
    Falcon::Color m_color;
    int m_tileIndex = 0;
    float m_angle;

};


#endif

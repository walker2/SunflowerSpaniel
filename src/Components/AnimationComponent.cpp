#include "AnimationComponent.h"


void AnimationComponent::init(tinyxml2::XMLNode *pNode)
{
    tinyxml2::XMLElement *pTextureElement = pNode->FirstChildElement("Texture");

    if (pTextureElement)
    {
        pTextureElement->QueryFloatAttribute("tileSize", &m_tileSize);
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


    tinyxml2::XMLElement *pAnimSpeedElement = pNode->FirstChildElement("AnimationSpeed");

    if (pAnimSpeedElement)
    {
        pAnimSpeedElement->QueryFloatText(&m_animSpeed);
    }

    tinyxml2::XMLElement *pFrameCountElement = pNode->FirstChildElement("FrameCount");

    if (pFrameCountElement)
    {
        pFrameCountElement->QueryIntText(&m_frameCount);
    }
}

void AnimationComponent::update(GameObject *obj, float /*deltaTime*/)
{
    m_body = obj->getComponent<BodyComponent>()->getBody();
    m_destRect.x = (m_body->GetPosition().x - m_spriteDims.x / 2.0f) + m_spritePos.x;
    m_destRect.y = (m_body->GetPosition().y - m_spriteDims.y / 2.0f) + m_spritePos.y;
    m_destRect.z = m_spriteDims.x;
    m_destRect.w = m_spriteDims.y;
    m_angle = m_body->GetAngle();
    m_direction = obj->getDirection();
}

void AnimationComponent::draw(Falcon::SpriteBatch &spriteBatch, float deltaTime)
{
    if (m_tileIndex != -1)
    {

        int tileIndex;
        tileIndex = m_tileIndex;

        // Increment animation tile
        m_animTime += m_animSpeed * deltaTime;

        // Apply animation
        tileIndex = tileIndex + (int) m_animTime % m_frameCount;

        spriteBatch.draw(m_destRect, m_tileSheet.getUVs(tileIndex), m_tileSheet.texture.id, 0.0f, m_color, m_angle);
    } else
    {
        glm::vec4 uvRect(0.0, 0.0, 1.0, 1.0);
        spriteBatch.draw(m_destRect, uvRect, m_tileSheet.texture.id, 0.0f, m_color, m_angle);
    }
}

void AnimationComponent::setTileSheet(const std::string &filePath)
{
    Falcon::GLTexture texture = Falcon::ResourceManager::getTexture(filePath);
    m_tileSheet.init(texture, glm::ivec2(texture.width / m_tileSize, texture.height / m_tileSize));
}

#include "DirectionalAnimationComponent.h"

void DirectionalAnimationComponent::draw(Falcon::SpriteBatch &spriteBatch, float deltaTime)
{
    if (m_tileIndex != -1)
    {
        int frameCount = 1;
        int tileIndex = 0;
        tileIndex = m_tileIndex;

        switch (m_direction)
        {
            case DIRECTION::LEFT:
                m_tileIndex = m_tileIndexLeftDir;
                break;
            case DIRECTION::RIGHT:
                m_tileIndex = m_tileIndexRightDir;
                break;
            case DIRECTION::UP:
                m_tileIndex = m_tileIndexUpDir;
                break;
            case DIRECTION::DOWN:
                m_tileIndex = m_tileIndexDownDir;
                break;
            case DIRECTION::LEFT_UP:
                m_tileIndex = m_tileIndexLeftUpDir;
                break;
            case DIRECTION::LEFT_DOWN:
                m_tileIndex = m_tileIndexLeftDownDir;
                break;
            case DIRECTION::RIGHT_UP:
                m_tileIndex = m_tileIndexRightUpDir;
                break;
            case DIRECTION::RIGHT_DOWN:
                m_tileIndex = m_tileIndexRightDownDir;
                break;
            case DIRECTION::NONE:
                m_tileIndex = m_tileIndexLeftDir;
                break;
        }

        if (m_body)
        {
            if (abs(m_body->GetLinearVelocity().x) > 1.0f || abs(m_body->GetLinearVelocity().y) > 1.0f)
            {
                frameCount = m_frameCount;
            }
        }

        // Increment animation tile
        m_animTime += m_animSpeed * deltaTime;

        // Apply animation
        tileIndex = tileIndex + (int) m_animTime % frameCount;

        spriteBatch.draw(m_destRect, m_tileSheet.getUVs(tileIndex), m_tileSheet.texture.id, 0.0f, m_color, m_angle);
    } else
    {
        glm::vec4 uvRect(0.0, 0.0, 1.0, 1.0);
        spriteBatch.draw(m_destRect, uvRect, m_tileSheet.texture.id, 0.0f, m_color, m_angle);
    }
}

void DirectionalAnimationComponent::init(tinyxml2::XMLNode *pNode)
{
    AnimationComponent::init(pNode);

    tinyxml2::XMLElement *pSpriteID = pNode->FirstChildElement("SpriteID");

    if (pSpriteID)
    {
        pSpriteID->QueryIntAttribute("left", &m_tileIndexLeftDir);
        pSpriteID->QueryIntAttribute("right", &m_tileIndexRightDir);
        pSpriteID->QueryIntAttribute("up", &m_tileIndexUpDir);
        pSpriteID->QueryIntAttribute("down", &m_tileIndexDownDir);
        pSpriteID->QueryIntAttribute("leftUp", &m_tileIndexLeftUpDir);
        pSpriteID->QueryIntAttribute("leftDown", &m_tileIndexLeftDownDir);
        pSpriteID->QueryIntAttribute("rightUp", &m_tileIndexRightUpDir);
        pSpriteID->QueryIntAttribute("rightDown", &m_tileIndexRightDownDir);
    }

}

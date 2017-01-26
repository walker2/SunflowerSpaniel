//
// Created by andrewshipilo on 1/26/17.
//

#include "OakTree.h"

void OakTree::drawToSpriteBatch(Falcon::SpriteBatch &spriteBatch)
{
    // Generate the oak
    // Draw the trunk
    spriteBatch.draw(
            m_position,
            m_tileSheet.getUVs(336),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x - m_tileSize, m_position.y , m_position.z, m_position.w),
            m_tileSheet.getUVs(335),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x + m_tileSize, m_position.y , m_position.z, m_position.w),
            m_tileSheet.getUVs(337),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x, m_position.y - m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(304),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));

    // Generate upper trunk
    spriteBatch.draw(
            glm::vec4(m_position.x, m_position.y + m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(398),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));

    // Generate leafs
    // First row
    spriteBatch.draw(
            glm::vec4(m_position.x, m_position.y + m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(368),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x + m_tileSize, m_position.y + m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(369),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x - m_tileSize, m_position.y + m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(367),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));

    // Second row
    spriteBatch.draw(
            glm::vec4(m_position.x, m_position.y + 2 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(400),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x + m_tileSize, m_position.y + 2 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(401),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x - m_tileSize, m_position.y + 2 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(399),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));

    // Third row
    spriteBatch.draw(
            glm::vec4(m_position.x, m_position.y + 3 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(432),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x + m_tileSize, m_position.y + 3 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(433),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x - m_tileSize, m_position.y + 3 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(431),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
}


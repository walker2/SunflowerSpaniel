#include "EvergreenTree.h"


void EvergreenTree::drawToSpriteBatch(Falcon::SpriteBatch& spriteBatch)
{
    // Draw the trunk
    spriteBatch.draw(
            m_position,
            m_tileSheet.getUVs(339),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x - m_tileSize, m_position.y , m_position.z, m_position.w),
            m_tileSheet.getUVs(338),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x + m_tileSize, m_position.y , m_position.z, m_position.w),
            m_tileSheet.getUVs(340),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x, m_position.y - m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(307),
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
            m_tileSheet.getUVs(371),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x + m_tileSize, m_position.y + m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(372),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x - m_tileSize, m_position.y + m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(370),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));

    // Second row
    spriteBatch.draw(
            glm::vec4(m_position.x, m_position.y + 2 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(403),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x + m_tileSize, m_position.y + 2 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(404),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x - m_tileSize, m_position.y + 2 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(402),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));

    // Third row
    spriteBatch.draw(
            glm::vec4(m_position.x, m_position.y + 3 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(435),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x + m_tileSize, m_position.y + 3 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(436),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    spriteBatch.draw(
            glm::vec4(m_position.x - m_tileSize, m_position.y + 3 * m_tileSize , m_position.z, m_position.w),
            m_tileSheet.getUVs(434),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
}

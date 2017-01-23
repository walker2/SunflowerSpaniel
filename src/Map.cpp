#include <Falcon/ResourceManager/ResourceManager.h>
#include <iostream>
#include "Map.h"

void Map::init(int mapWidth, int mapHeight, const std::string tileSheetPath, int tileSize)
{
    m_height = mapHeight;
    m_width = mapWidth;
    m_tileSize = tileSize / 20;
    Falcon::GLTexture texture = Falcon::ResourceManager::getTexture(tileSheetPath);

    m_tileSheet.init(texture, glm::ivec2(texture.width / tileSize, texture.height / tileSize));
    m_value.resize(m_height);
    for (auto& val : m_value)
    {
        val.resize(m_width);
    }
}

void Map::generateMap()
{
    for (double y = 0; y < m_height; y++)
    {
        for (double x = 0; x < m_width; x++)
        {
            double nx = x / m_width - 0.5,
                   ny = y / m_height - 0.5;
            double e = (1.00 * noise( 1 * nx,  1 * ny)
                     + 0.50 * noise( 2 * nx,  2 * ny)
                     + 0.25 * noise( 4 * nx,  4 * ny)
                     + 0.13 * noise( 8 * nx,  8 * ny)
                     + 0.06 * noise(16 * nx, 16 * ny)
                     + 0.03 * noise(32 * nx, 32 * ny));
            e /= (1.00+0.50+0.25+0.13+0.06+0.03);
            m_value[x][y] = e;
        }
    }
    m_gen.SetSeed(time(0));
    m_spriteBatch.init();
    m_spriteBatch.begin();
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            double tile = m_value[y][x];
            glm::vec4 posVec(y * m_tileSize, x * m_tileSize, m_tileSize, m_tileSize);

            switch (biome(tile))
            {

                case BIOME::WATER:
                    m_spriteBatch.draw(
                            posVec,
                            m_tileSheet.getUVs(465),
                            m_tileSheet.texture.id,
                            0.0f,
                            Falcon::Color(255, 255, 225, 255));
                    break;
                case BIOME::BEACH:
                    m_spriteBatch.draw(
                            posVec,
                            m_tileSheet.getUVs(658),
                            m_tileSheet.texture.id,
                            0.0f,
                            Falcon::Color(255, 255, 225, 255));
                    break;
                case BIOME::FOREST:
                    m_spriteBatch.draw(
                            posVec,
                            m_tileSheet.getUVs(641),
                            m_tileSheet.texture.id,
                            0.0f,
                            Falcon::Color(255, 255, 225, 255));
                    break;
                case BIOME::JUNGLE:
                    m_spriteBatch.draw(
                            posVec,
                            m_tileSheet.getUVs(647),
                            m_tileSheet.texture.id,
                            0.0f,
                            Falcon::Color(255, 255, 225, 255));
                    break;
                case BIOME::SAVANNAH:
                    m_spriteBatch.draw(
                            posVec,
                            m_tileSheet.getUVs(834),
                            m_tileSheet.texture.id,
                            0.0f,
                            Falcon::Color(255, 255, 225, 255));
                    break;
                case BIOME::DESERT:
                    m_spriteBatch.draw(
                            posVec,
                            m_tileSheet.getUVs(837),
                            m_tileSheet.texture.id,
                            0.0f,
                            Falcon::Color(255, 255, 225, 255));
                    break;
                case BIOME::SNOW:
                    m_spriteBatch.draw(
                            posVec,
                            m_tileSheet.getUVs(466),
                            m_tileSheet.texture.id,
                            0.0f,
                            Falcon::Color(255, 255, 225, 255));
                    break;
            }
        }
    }
    m_spriteBatch.end();
    m_isGenerated = true;
}

double Map::noise(double nx, double ny)
{
    // Rescale from -1.0:+1.0 to 0.0:1.0
    return (m_gen.GetValue(nx, ny, 0) / 2.0f + 0.5f);
}

BIOME Map::biome(double val)
{
    if (val < 0.45) return BIOME::WATER;
    else if (val < 0.5) return BIOME::BEACH;
    else if (val < 0.6) return BIOME::FOREST;
    else if (val < 0.65) return BIOME::JUNGLE;
    else if (val < 0.7) return BIOME::SAVANNAH;
    else if (val < 0.8) return BIOME::DESERT;
    else return BIOME::SNOW;
}

void Map::draw()
{
    m_spriteBatch.renderBatch();
}


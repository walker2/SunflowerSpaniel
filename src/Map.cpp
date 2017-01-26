#include <Falcon/ResourceManager/ResourceManager.h>
#include <iostream>
#include <random>
#include "Map.h"

void Map::init(b2World *world, int mapWidth, int mapHeight, const std::string tileSheetPath, int tileSize)
{
    m_height = mapHeight;
    m_width = mapWidth;
    m_tileSize = tileSize / 10;
    m_world = world;
    Falcon::GLTexture texture = Falcon::ResourceManager::getTexture(tileSheetPath);

    m_tileSheet.init(texture, glm::ivec2(texture.width / tileSize, texture.height / tileSize));
    m_value.resize(m_height);
    for (auto& val : m_value)
    {
        val.resize(m_width);
    }
    m_gen.SetSeed(time(0));
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
            e /= (1.00 + 0.50 + 0.25 + 0.13 + 0.06 + 0.03);
            m_value[x][y] = e;
        }
    }
    std::mt19937 rng(time(0));
    m_gen.SetSeed(time(0));

    if (m_isGenerated)
    {
        for (auto& tree : m_evergreens)
        {
            tree.getCollision()->destroy();
        }
        for (auto& tree : m_oaks)
        {
            tree.getCollision()->destroy();
        }

        m_evergreens.clear();
        m_oaks.clear();
    }

    m_layerOneSpriteBatch.init();
    m_layerOneSpriteBatch.begin();

    // Generate first layer (background)
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            double tile = m_value[y][x];
            glm::vec4 posVec(y * m_tileSize, x * m_tileSize, m_tileSize, m_tileSize);

            switch (biome(tile))
            {

                case BIOME::WATER:
                    generateWater(posVec, rng);
                    break;
                case BIOME::BEACH:
                    generateBeach(posVec, rng);
                    break;
                case BIOME::FOREST:
                    generateForest(posVec, rng);
                    break;
                case BIOME::JUNGLE:
                    generateJungle(posVec, rng);
                    break;
                case BIOME::SAVANNAH:
                    generateSavannah(posVec, rng);
                    break;
                case BIOME::DESERT:
                    generateDesert(posVec, rng);
                    break;
                case BIOME::SNOW:
                    generateSnow(posVec, rng);
                    break;
            }
        }
    }
    m_layerOneSpriteBatch.end();

    m_layerTwoSpriteBatch.init();
    m_layerTwoSpriteBatch.begin();
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    // Generate second layer (trees)
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            double tile = m_value[y][x];
            glm::vec4 posVec(y * m_tileSize, x * m_tileSize, m_tileSize, m_tileSize);

            switch (biome(tile))
            {

                case BIOME::WATER:
                    // EMPTY
                    break;
                case BIOME::BEACH:
                    // EMPTY
                    break;
                case BIOME::FOREST:
                    if (chance(rng) > 0.98f)
                    {
                        // Generate the tree
                        if (chance(rng) > 0.5f)
                        {
                            // Generate the oak
                            OakTree tree(m_world, posVec, m_tileSheet, m_tileSize);
                            tree.drawToSpriteBatch(m_layerTwoSpriteBatch);
                            m_oaks.push_back(tree);
                        }
                        else
                        {
                            // Generate evergreen
                            EvergreenTree tree(m_world, posVec, m_tileSheet, m_tileSize);
                            tree.drawToSpriteBatch(m_layerTwoSpriteBatch);
                            m_evergreens.push_back(tree);
                        }
                    }
                    break;
                case BIOME::JUNGLE:
                    // EMPTY
                    break;
                case BIOME::SAVANNAH:
                    // EMPTY
                    break;
                case BIOME::DESERT:
                    // EMPTY
                    break;
                case BIOME::SNOW:
                    // EMPTY
                    break;
            }
        }
    }

    m_layerTwoSpriteBatch.end();
    m_isGenerated = true;
}

void Map::generateWater(glm::vec4& posVec, std::mt19937& rng)
{
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    m_layerOneSpriteBatch.draw(
            posVec,
            m_tileSheet.getUVs(924),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));

    if (chance(rng) > 0.9f)
    {
        if (chance(rng) > 0.5f)
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(859),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
        else
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(860),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
    }
}

void Map::generateBeach(glm::vec4& posVec, std::mt19937& rng)
{
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    if (chance(rng) > 0.5f)
    {
        m_layerOneSpriteBatch.draw(
                posVec,
                m_tileSheet.getUVs(658),
                m_tileSheet.texture.id,
                0.0f,
                Falcon::Color(255, 255, 225, 255));
    }
    else
    {
        if (chance(rng) > 0.5f)
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(659),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
        else
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(660),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
    }
}

void Map::generateForest(glm::vec4& posVec, std::mt19937& rng)
{
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    if (chance(rng) > 0.5f)
    {
        // Generate simple grass
        m_layerOneSpriteBatch.draw(
                posVec,
                m_tileSheet.getUVs(642),
                m_tileSheet.texture.id,
                0.0f,
                Falcon::Color(255, 255, 225, 255));
    }
    else
    {
        if (chance(rng) > 0.3f)
        {
            // Generate low grass
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(641),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
        else
        {
            // Generate high grass
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(640),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
    }

    if (chance(rng) > 0.9f)
    {
        if (chance(rng) > 0.2f)
        {
            // Generate mini bush
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(655),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));

            return;
        }
    }

}

void Map::generateJungle(glm::vec4& posVec, std::mt19937& rng)
{
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    if (chance(rng) > 0.5f)
    {
        // Generate simple grass
        m_layerOneSpriteBatch.draw(
                posVec,
                m_tileSheet.getUVs(648),
                m_tileSheet.texture.id,
                0.0f,
                Falcon::Color(255, 255, 225, 255));
    }
    else
    {
        if (chance(rng) > 0.3f)
        {
            // Generate low grass
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(647),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
        else
        {
            // Generate high grass
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(646),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
    }
}

void Map::generateSavannah(glm::vec4& posVec, std::mt19937& rng)
{
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    m_layerOneSpriteBatch.draw(
            posVec,
            m_tileSheet.getUVs(834),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    if (chance(rng) > 0.985f)
    {
        // Generate big boulders
        if (chance(rng) > 0.7f)
        {
            // First part of boulder
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(412),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
            // Second part
            m_layerOneSpriteBatch.draw(
                    glm::vec4(posVec.x, posVec.y - m_tileSize, posVec.z, posVec.w),
                    m_tileSheet.getUVs(380),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
        else
        {
            // Generate one big boulder
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(415),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
        return;
    }

    if (chance(rng) > 0.9f)
    {
        // Generate small stones
        if (chance(rng) > 0.5f)
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(413),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
        else
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(414),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
        return;
    }
}

void Map::generateDesert(glm::vec4& posVec, std::mt19937& rng)
{
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    // Generate simple desert tiles
    m_layerOneSpriteBatch.draw(
            posVec,
            m_tileSheet.getUVs(837),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
    if (chance(rng) > 0.9f)
    {
        // Generate some stones or boulders
        if (chance(rng) > 0.5f)
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(447),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
        else
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(445),
                    m_tileSheet.texture.id,
                    0.0f,
                    Falcon::Color(255, 255, 225, 255));
        }
    }
}

void Map::generateSnow(glm::vec4& posVec, std::mt19937& rng)
{
    m_layerOneSpriteBatch.draw(
            posVec,
            m_tileSheet.getUVs(466),
            m_tileSheet.texture.id,
            0.0f,
            Falcon::Color(255, 255, 225, 255));
}

double Map::noise(double nx, double ny)
{
    // Rescale from -1.0:+1.0 to 0.0:1.0
    return (m_gen.GetValue(nx, ny, 0) / 2.0f + 0.5f);
}

BIOME Map::biome(double val)
{
         if (val < 0.35) return BIOME::WATER;
    else if (val < 0.40) return BIOME::BEACH;
    else if (val < 0.55) return BIOME::FOREST;
    else if (val < 0.65) return BIOME::JUNGLE;
    else if (val < 0.75) return BIOME::SAVANNAH;
    else if (val < 0.85) return BIOME::DESERT;
    else return BIOME::SNOW;
}

void Map::drawDebug(Falcon::DebugRenderer &debugRenderer)
{
    // Draw evergreen debug
    for (auto& tree : m_evergreens)
    {
        tree.drawDebug(debugRenderer);
    }
    // Draw oaks debug
    for (auto& tree : m_oaks)
    {
        tree.drawDebug(debugRenderer);
    }
}

void Map::drawBackground()
{
    m_layerOneSpriteBatch.renderBatch();
}

void Map::drawForeground()
{
    m_layerTwoSpriteBatch.renderBatch();
}


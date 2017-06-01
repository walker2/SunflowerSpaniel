#include <Falcon/ResourceManager/ResourceManager.h>
#include <random>
#include "../ObjectFactory/ObjectFactory.h"
#include "Map.h"

GridWithWeights make_diagram_for_play_field()
{
    GridWithWeights grid(200, 200);
    add_rect(grid, 1, 7, 4, 9);
    return grid;
}

void Map::init(b2World */*world*/, int mapWidth, int mapHeight, const std::string tileSheetPath, int tileSize)
{
    // TODO: ADD AREAS OF NOT SPAWNING TREES
    m_height = mapHeight;
    m_width = mapWidth;
    m_tileSize = tileSize / 10;
    m_colorTint.setColor(255, 255, 255);
    Falcon::GLTexture texture = Falcon::ResourceManager::getTexture(tileSheetPath);
    Falcon::GLTexture transTexture = Falcon::ResourceManager::getTexture("media/Textures/TransitionsWithRoad.png");

    m_tileSheet.init(texture, glm::ivec2(texture.width / tileSize, texture.height / tileSize));
    m_tileSheet2.init(transTexture, glm::ivec2(transTexture.width / tileSize, transTexture.height / tileSize));
    m_value.resize(m_height);
    for (auto &val : m_value)
    {
        val.resize(m_width);
    }
    m_grid = make_diagram_for_play_field();
}

void Map::generateMap()
{

    m_rng.seed(time(0));
    m_gen.SetSeed(time(0));

    for (double y = 0; y < m_height; y++)
    {
        for (double x = 0; x < m_width; x++)
        {
            double nx = x / m_width - 0.5,
                    ny = y / m_height - 0.5;
            double e = (1.00 * noise(1 * nx, 1 * ny)
                        + 0.50 * noise(2 * nx, 2 * ny)
                        + 0.25 * noise(4 * nx, 4 * ny)
                        + 0.13 * noise(8 * nx, 8 * ny)
                        + 0.06 * noise(16 * nx, 16 * ny)
                        + 0.03 * noise(32 * nx, 32 * ny));
            e /= (1.00 + 0.50 + 0.25 + 0.13);
            m_value[x][y] = e;
        }
    }
    std::shared_ptr<GameObject> redInn = ObjectFactory::instance().createObject("media/Objects/RedINN.xml");
    redInn->setLayer(3);
    ObjectFactory::instance().addObject(redInn);
    SquareGrid::Location redInnPos{redInn->getComponent<BodyComponent>()->getPosition().x / 3,
                                   redInn->getComponent<BodyComponent>()->getPosition().y / 3};

    std::shared_ptr<GameObject> redMonk = ObjectFactory::instance().createObject("media/Objects/RedMonk.xml");
    redMonk->setLayer(3);
    ObjectFactory::instance().addObject(redMonk);

    std::shared_ptr<GameObject> blueInn = ObjectFactory::instance().createObject("media/Objects/BlueINN.xml");
    blueInn->setLayer(3);
    ObjectFactory::instance().addObject(blueInn);
    SquareGrid::Location blueInnPos{blueInn->getComponent<BodyComponent>()->getPosition().x / 3,
                                    blueInn->getComponent<BodyComponent>()->getPosition().y / 3};

    std::shared_ptr<GameObject> blueMonk = ObjectFactory::instance().createObject("media/Objects/BlueMonk.xml");
    blueMonk->setLayer(3);
    ObjectFactory::instance().addObject(blueMonk);

    std::shared_ptr<GameObject> greenInn = ObjectFactory::instance().createObject("media/Objects/GreenINN.xml");
    greenInn->setLayer(3);
    ObjectFactory::instance().addObject(greenInn);
    SquareGrid::Location greenInnPos{greenInn->getComponent<BodyComponent>()->getPosition().x / 3,
                                     greenInn->getComponent<BodyComponent>()->getPosition().y / 3};

    std::shared_ptr<GameObject> greenMonk = ObjectFactory::instance().createObject("media/Objects/GreenMonk.xml");
    greenMonk->setLayer(3);
    ObjectFactory::instance().addObject(greenMonk);

    generateRoad(redInnPos, blueInnPos);
    generateRoad(blueInnPos, greenInnPos);
    generateRoad(greenInnPos, redInnPos);

    m_layerOneSpriteBatch.init();
    m_layerOneSpriteBatch.begin();

    std::uniform_real_distribution<float> chance(0.0f, 1.0f);
    // Generate first layer (background)
    for (int y = 1; y < m_height - 1; y++)
    {
        for (int x = 1; x < m_width - 1; x++)
        {
            double tile = m_value[y][x];

            glm::vec4 posVec(x * m_tileSize, y * m_tileSize, m_tileSize, m_tileSize);
            BIOME sTL = biome(m_value[y + 1][x - 1]);
            BIOME sT = biome(m_value[y + 1][x]);
            BIOME sTR = biome(m_value[y + 1][x + 1]);
            BIOME sL = biome(m_value[y][x - 1]);
            BIOME sM = biome(m_value[y][x]);
            BIOME sR = biome(m_value[y][x + 1]);
            BIOME sBL = biome(m_value[y - 1][x - 1]);
            BIOME sB = biome(m_value[y - 1][x]);
            BIOME sBR = biome(m_value[y - 1][x + 1]);

            if (sM == BIOME::WATER)
            {
                generateWater(posVec, tile);
            } else
            {
                int index = calculateTileIndex(sTL, sT, sTR, sL, sR, sBL, sB, sBR,
                                               static_cast<BIOME>(static_cast<int>(sM) - 1));

                int startTile = (992 - static_cast<int>(sM) * 32);
                m_layerOneSpriteBatch.draw(
                        posVec,
                        m_tileSheet2.getUVs(startTile + index),
                        m_tileSheet2.texture.id,
                        0.0f,
                        m_colorTint);

                if (index > 15)
                {
                    generateMisc(posVec, startTile);
                }
            }
        }
    }
    m_layerOneSpriteBatch.end();

    m_layerTwoSpriteBatch.init();
    m_layerTwoSpriteBatch.begin();
    // Generate second layer (trees)
    for (int y = m_height - 1; y > 0; y--)
    {
        for (int x = m_width - 1; x > 0; x--)
        {
            double tile = m_value[y][x];
            glm::vec4 posVec(x * m_tileSize, y * m_tileSize, m_tileSize, m_tileSize);

            switch (biome(tile))
            {
                case BIOME::WATER:
                    // EMPTY
                    break;
                case BIOME::BEACH:
                    // EMPTY
                    break;
                case BIOME::FOREST:
                    if (chance(m_rng) > 0.95f && (posVec.x < 430 || posVec.x > 470) && (posVec.y < 430 || posVec.y >
                                                                                                          470)) // SHOULD BE ANOTHER FOR THAT CHECKS RESTRICTED AREAS FOR GENERATION
                    {
                        // Generate the tree
                        if (chance(m_rng) > 0.5f)
                        {
                            // Generate the oak
                            std::shared_ptr<GameObject> oak = ObjectFactory::instance().createObject(
                                    "media/Objects/Oak.xml");
                            oak->getComponent<BodyComponent>()->setPosition(glm::vec2(posVec.x, posVec.y));
                            oak->setLayer(2);
                            ObjectFactory::instance().addObject(oak);
                        }
                    }
                    break;
                case BIOME::JUNGLE:
                    if (chance(m_rng) > 0.95f)
                    {
                        // Generate the tree
                        if (chance(m_rng) > 0.5f)
                        {
                            // Generate evergreen
                            std::shared_ptr<GameObject> evergreen = ObjectFactory::instance().createObject(
                                    "media/Objects/Evergreen.xml");
                            evergreen->getComponent<BodyComponent>()->setPosition(glm::vec2(posVec.x, posVec.y));
                            evergreen->setLayer(2);
                            ObjectFactory::instance().addObject(evergreen);
                        }
                    }
                    break;
                case BIOME::SAVANNAH:
                    // EMPTY
                    break;
                case BIOME::ROCKS:
                    // EMPTY
                    break;
                case BIOME::SNOW:
                    // EMPTY
                    break;
                case BIOME::ROAD:
                    break;
            }
        }
    }

    m_layerTwoSpriteBatch.end();
    m_isGenerated = true;
}

void Map::generateWater(glm::vec4 &posVec, double val)
{
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    double diff = 1.0;
    Falcon::Color color;
    Falcon::Color color1;
    if (val > 0.1)
    {
        diff = (0.35 - val) * 4;
        color.setColor(m_colorTint.r * diff, m_colorTint.g * diff, m_colorTint.b);
        color1.setColor(m_colorTint.r - color.r, m_colorTint.g - color.g, m_colorTint.b);
    } else
    {
        color1.setColor(0, 0, 255);
    }

    m_layerOneSpriteBatch.draw(
            posVec,
            m_tileSheet.getUVs(924),
            m_tileSheet.texture.id,
            0.0f,
            color1);

    if (chance(m_rng) > 0.9f)
    {
        if (chance(m_rng) > 0.5f)
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(859),
                    m_tileSheet.texture.id,
                    0.0f,
                    color1);
        } else
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet.getUVs(860),
                    m_tileSheet.texture.id,
                    0.0f,
                    color1);
        }
    }
}

void Map::generateMisc(glm::vec4 &posVec, int startingTile)
{
    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    if (chance(m_rng) > 0.9f)
    {
        // Generate some stones or boulders
        if (chance(m_rng) > 0.2f)
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet2.getUVs(startingTile + 19),
                    m_tileSheet2.texture.id,
                    0.0f,
                    m_colorTint);
        } else
        {
            m_layerOneSpriteBatch.draw(
                    posVec,
                    m_tileSheet2.getUVs(startingTile + 20),
                    m_tileSheet2.texture.id,
                    0.0f,
                    m_colorTint);
        }
    }
}

double Map::noise(double nx, double ny)
{
    // Rescale from -1.0:+1.0 to 0.0:1.0
    return (m_gen.GetValue(nx, ny, 0) / 2.0f + 0.5f);
}

BIOME Map::biome(double val)
{
    if (val == -1) return BIOME::ROAD;
    else if (val <= 0.15) return BIOME::WATER; //35
    else if (val <= 0.25) return BIOME::BEACH; //40
    else if (val <= 0.55) return BIOME::FOREST; //55
    else if (val <= 0.65) return BIOME::JUNGLE; //65
    else if (val <= 0.75) return BIOME::SAVANNAH; //75
    else if (val <= 0.85) return BIOME::ROCKS; //85
    else return BIOME::SNOW;
}

void Map::drawBackground()
{
    m_layerOneSpriteBatch.renderBatch();
}

void Map::drawForeground()
{
    m_layerTwoSpriteBatch.renderBatch();
}

int
Map::calculateTileIndex(BIOME sTL, BIOME sT, BIOME sTR, BIOME sL, BIOME sR, BIOME sBL, BIOME sB, BIOME sBR, BIOME trans)
{
    int index = 0;

    std::uniform_real_distribution<float> chance(0.0f, 1.0f);

    if (sTL != trans && sT != trans && sL != trans)
    {
        index += 1;
    }
    if (sT != trans && sTR != trans && sR != trans)
    {
        index += 2;
    }
    if (sL != trans && sBL != trans && sB != trans)
    {
        index += 4;
    }
    if (sR != trans && sBR != trans && sB != trans)
    {
        index += 8;
    }

    if (index == 15)
    {
        if (chance(m_rng) > 0.9f)
        {
            if (chance(m_rng) > 0.7f)
            {
                index += 1;
            } else
            {
                index += 2;
            }
        } else
        {
            if (chance(m_rng) > 0.7f)
            {
                index += 3;
            }
        }
    }
    return index;
}

void Map::generateRoad(SquareGrid::Location start, SquareGrid::Location goal)
{
    unordered_map<SquareGrid::Location, SquareGrid::Location> came_from;
    unordered_map<SquareGrid::Location, double> cost_so_far;
    a_star_search(m_grid, start, goal, came_from, cost_so_far);

    vector<SquareGrid::Location> path = reconstruct_path(start, goal, came_from);

    for (auto itr = path.begin(); itr != path.end(); itr++)
    {
        m_value[std::get<1>(*itr)][std::get<0>(*itr)] = -1;

    }
}



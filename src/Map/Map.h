#ifndef SUNFLOWERSPANIEL_MAP_H
#define SUNFLOWERSPANIEL_MAP_H


#include <Falcon/2D/TileSheet.h>
#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include <noise.h>
#include <Box2D/Box2D.h>
#include <random>

#include "../ObjectFactory/GameObject.h"

enum class BIOME
{
    WATER = -1, BEACH, FOREST, JUNGLE, SAVANNAH, ROCKS, SNOW
};

class Map
{
public:
    Map()
    {}

    ~Map()
    {}

    void init(b2World *world, int mapWidth, int mapHeight, const std::string tileSheetPath, int tileSize,
              std::vector<std::shared_ptr<GameObject>> *gameObjects);

    void generateMap();

    void drawBackground();

    void drawForeground();

    void dispose()
    { m_value.clear(); }

    bool isGenerated()
    { return m_isGenerated; }

private:
    double noise(double nx, double ny);

    int calculateTileIndex(BIOME sTL, BIOME sT, BIOME sTR,
                           BIOME sL, BIOME sR, BIOME sBL,
                           BIOME sB, BIOME sBR, BIOME trans);

    BIOME biome(double val);

    void generateWater(glm::vec4 &posVec, double val);

    void generateMisc(glm::vec4 &posVec, int startingTile);


private:
    bool m_isGenerated = false;
    int m_width = 0;
    int m_height = 0;
    int m_tileSize = 0;

    Falcon::Color m_colorTint;
    Falcon::TileSheet m_tileSheet;
    Falcon::TileSheet m_tileSheet2;
    Falcon::SpriteBatch m_layerOneSpriteBatch;
    Falcon::SpriteBatch m_layerTwoSpriteBatch;

    std::vector<std::shared_ptr<GameObject>> *m_gameObjects;
    noise::module::Perlin m_gen;
    std::vector<std::vector<double>> m_value;
    std::mt19937 m_rng;

};


#endif

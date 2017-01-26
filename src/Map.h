#ifndef SUNFLOWERSPANIEL_MAP_H
#define SUNFLOWERSPANIEL_MAP_H


#include <Falcon/2D/TileSheet.h>
#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include <libnoise/noise.h>
#include <Box2D/Box2D.h>

#include "EvergreenTree.h"
#include "OakTree.h"

enum class BIOME { WATER = 0, BEACH, FOREST, JUNGLE, SAVANNAH, DESERT, SNOW};
class Map
{
public:
    Map() {};
    ~Map() {};

    void init(b2World *world, int mapWidth, int mapHeight, const std::string tileSheetPath, int tileSize);
    void generateMap();
    void drawBackground();
    void drawForeground();
    void drawDebug(Falcon::DebugRenderer &debugRenderer);

    bool isGenerated() { return m_isGenerated; };

private:
    double noise(double nx, double ny);
    BIOME biome(double val);
    void generateWater(glm::vec4& posVec, std::mt19937& rng);
    void generateBeach(glm::vec4& posVec, std::mt19937& rng);
    void generateForest(glm::vec4& posVec, std::mt19937& rng);
    void generateJungle(glm::vec4& posVec, std::mt19937& rng);
    void generateSavannah(glm::vec4& posVec, std::mt19937& rng);
    void generateDesert(glm::vec4& posVec, std::mt19937& rng);
    void generateSnow(glm::vec4& posVec, std::mt19937& rng);


private:
    bool m_isGenerated = false;
    int m_width = 0;
    int m_height = 0;
    int m_tileSize = 0;
    Falcon::TileSheet m_tileSheet;
    Falcon::SpriteBatch m_layerOneSpriteBatch;
    Falcon::SpriteBatch m_layerTwoSpriteBatch;
    b2World* m_world;
    noise::module::Perlin m_gen;
    std::vector<std::vector<double>> m_value;
    std::vector<EvergreenTree> m_evergreens;
    std::vector<OakTree> m_oaks;
};


#endif

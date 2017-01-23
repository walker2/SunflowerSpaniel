#ifndef SUNFLOWERSPANIEL_MAP_H
#define SUNFLOWERSPANIEL_MAP_H


#include <Falcon/2D/TileSheet.h>
#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include <libnoise/noise.h>

enum class BIOME { WATER = 0, BEACH, FOREST, JUNGLE, SAVANNAH, DESERT, SNOW};
class Map
{
public:
    Map() {};
    ~Map() {};

    void init(int mapWidth, int mapHeight, const std::string tileSheetPath, int tileSize);
    void generateMap();
    void draw();

    bool isGenerated() { return m_isGenerated; };

private:
    double noise(double nx, double ny);
    BIOME biome(double val);

private:
    bool m_isGenerated = false;
    int m_width = 0;
    int m_height = 0;
    int m_tileSize = 0;
    Falcon::TileSheet m_tileSheet;
    Falcon::SpriteBatch m_spriteBatch;
    noise::module::Perlin m_gen;
    std::vector<std::vector<double>> m_value;
};


#endif

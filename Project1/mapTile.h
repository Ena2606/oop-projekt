#ifndef MAPTILE_H
#define MAPTILE_H

#include <SFML/Graphics.hpp>
#include "Constants.h"

enum class HazardType
{
    None,
    FireFloor,
    WaterFloor,
    Spikes
};
enum class DiamondType {
    Fire,
    Water
};

class MapTile {
public:
    bool isPassable;
    bool isHazard = false;
    bool isExit;

    HazardType hazardType = HazardType::None;

    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;

    MapTile(std::string, float, float, bool, bool);
    bool setUpSprite(std::string);
    DiamondType diamondType = DiamondType::Fire;
    bool collected = false;

    int gridX = -1;
    int gridY = -1;

    std::string textureName;
};

#endif
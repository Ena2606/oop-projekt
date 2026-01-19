#include "mapTile.h"
#include "Constants.h"
MapTile::MapTile(std::string textureName, float x, float y, bool passable, bool exit)
{


    this->textureName = textureName;

    setUpSprite(textureName);


    sprite.setScale(
        TILE_SIZE / 50.f,
        TILE_SIZE / 50.f
    );

    pos = { x, y };
    sprite.setPosition(pos);

    isPassable = passable;
    isExit = exit;
}

bool MapTile::setUpSprite(std::string textureName)
{
    if (!texture.loadFromFile(textureName))
        return false;
    this->textureName = textureName;

    sprite.setTexture(texture);


    if (textureName == "poison_spike.png")
    {
        isHazard = true;
        isPassable =  true;
        hazardType = HazardType::Spikes;
    }
    else if (textureName == "water_floor.png")
    {
        isHazard = true;
        isPassable = true;
        hazardType = HazardType::WaterFloor;
    }
    else if (textureName == "fire_floor.png")
    {
        isHazard = true;
        isPassable = true;
        hazardType = HazardType::FireFloor;
    }
    else
    {
        hazardType = HazardType::None;
    }

    return true;
}
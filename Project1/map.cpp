#include "Map.h"
#include "MapTile.h"
#include "Constants.h"

Map::Map()
{
    gridLength = 51;
    gridHeight = 29;
    setUpInitialState();

}

float Map::getGroundY() const {
    return tiles[gridHeight - 1][0]->sprite.getPosition().y;
}

void Map::setUpInitialState()
{
    for (auto* diamond : diamonds)
        delete diamond;

    diamonds.clear();
    setUpTiles();

    for (auto* diamond : diamonds)
    {
        if (diamond)
            diamond->collected = false;
    }
}

void Map::setUpTiles()
{
    tiles.clear();
    tiles.resize(gridHeight,std::vector<MapTile*>(gridLength, nullptr));
    hazards.clear();
    hazards.resize(gridHeight,std::vector<MapTile*>(gridLength, nullptr));
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridLength; x++)
        {
            bool isBorder =
                x == 0 ||
                x == gridLength - 1 ||
                y == 0 ||
                y == gridHeight - 1;

            if (isBorder)
            {
                std::string texture =
                    (y == gridHeight - 1)
                    ? "platformPack_tile001.png"
                    : "platformPack_tile004.png";
                tiles[y][x] = new MapTile(texture, x * TILE_SIZE, y * TILE_SIZE, false, false);
            }
            else
            {
                tiles[y].push_back(nullptr);
            }
        }
    }
    int y = gridHeight - 6;
    for (int x = gridLength - 8; x < gridLength - 1; x++) {
        tiles[y][x] = new MapTile("platformPack_tile001.png", x * TILE_SIZE, y * TILE_SIZE, false, false);
    }
    y = gridHeight - 11;
    for (int x = 1; x < gridLength - 12; x++) {
        tiles[y][x] = new MapTile("platformPack_tile001.png", x * TILE_SIZE, y * TILE_SIZE, false, false);
    }
    y = gridHeight - 15;
    for (int x = 2; x < 6; x++) {
        tiles[y][x] = new MapTile("platformPack_tile001.png", x * TILE_SIZE, y * TILE_SIZE, false, false);
    }
    y = gridHeight - 18;
    for (int x = 10; x < gridLength - 1; x++) {
        tiles[y][x] = new MapTile("platformPack_tile004.png", x * TILE_SIZE, y * TILE_SIZE, false, false);
    }
    y = gridHeight - 19;
    for (int x = 10; x < gridLength - 1; x++) {
        tiles[y][x] = new MapTile("platformPack_tile001.png", x * TILE_SIZE, y * TILE_SIZE, false, false);
    }
    y = gridHeight - 19;
    for (int x = 28; x < gridLength - 20; x++) {
        MapTile* spike = new MapTile("poison_spike.png", x * TILE_SIZE, y * TILE_SIZE, false, false);
        tiles[y][x] = spike;
        hazards[y][x] = spike;
    }
    y = gridHeight - 1;
    for (int x = 28; x < gridLength - 20; x++) {
        MapTile* spike = new MapTile("fire_floor.png", x * TILE_SIZE, y * TILE_SIZE, false, false);
        tiles[y][x] = spike;
        hazards[y][x] = spike;

    }for (int x = 15; x < gridLength - 33; x++) {
        MapTile* spike = new MapTile("water_floor.png", x * TILE_SIZE, y * TILE_SIZE, false, false);
        tiles[y][x] = spike;
        hazards[y][x] = spike;

    }
    // Fire Door
    fireDoor = new MapTile("fire_door.png", (gridLength - 4) * TILE_SIZE, 0, true, true);
    float scale = 80.f / fireDoor->sprite.getLocalBounds().height;
    fireDoor->sprite.setScale(scale, scale);
    fireDoor->sprite.setPosition(
        fireDoor->sprite.getPosition().x - 20,
        (gridHeight - 2) * TILE_SIZE - 505
    );
    tiles[gridHeight - 2][gridLength - 4] = fireDoor;

    // Water Door
    waterDoor = new MapTile("water_door.png", (gridLength - 8) * TILE_SIZE, 0, true, true);
    scale = 80.f / waterDoor->sprite.getLocalBounds().height;
    waterDoor->sprite.setScale(scale, scale);
    waterDoor->sprite.setPosition(
        (gridLength - 8) * TILE_SIZE - 20,
        (gridHeight - 2) * TILE_SIZE - 505
    );
    tiles[gridHeight - 2][gridLength - 8] = waterDoor;

    //Dijamant
    //Fire dijamant 1 
    MapTile* fireDiamond = new MapTile("fire_diamond.png",8 * TILE_SIZE,(gridHeight - 3) * TILE_SIZE,true,true);
    fireDiamond->diamondType = DiamondType::Fire;
    fireDiamond->gridX = 8;
    fireDiamond->gridY = gridHeight - 3;

    diamonds.push_back(fireDiamond);
    tiles[gridHeight - 3][8] = fireDiamond;

    //2
    MapTile* fireDiamond2 = new MapTile("fire_diamond.png",15 * TILE_SIZE,(gridHeight - 8) * TILE_SIZE,true,true);
    fireDiamond2->diamondType = DiamondType::Fire;
    fireDiamond2->gridX = 15;
    fireDiamond2->gridY = gridHeight - 8;

    diamonds.push_back(fireDiamond2);
    tiles[gridHeight - 8][15] = fireDiamond2;

    //3
    MapTile* fireDiamond3 = new MapTile("fire_diamond.png", 47 * TILE_SIZE, (gridHeight - 9) * TILE_SIZE, true, true);
    fireDiamond3->diamondType = DiamondType::Fire;
    fireDiamond3->gridX = 47;
    fireDiamond3->gridY = gridHeight - 9;

    diamonds.push_back(fireDiamond3);
    tiles[gridHeight - 9][47] = fireDiamond3;

    //4
    MapTile* fireDiamond4 = new MapTile("fire_diamond.png", 18 * TILE_SIZE, (gridHeight - 25) * TILE_SIZE, true, true);
    fireDiamond4->diamondType = DiamondType::Fire;
    fireDiamond4->gridX = 18;
    fireDiamond4->gridY = gridHeight - 25;

    diamonds.push_back(fireDiamond4);
    tiles[gridHeight - 25][18] = fireDiamond4;


    // Water dijamant 1
    MapTile* waterDiamond = new MapTile("water_diamond.png", 10 * TILE_SIZE, (gridHeight - 5) * TILE_SIZE, true, true
    );

    waterDiamond->diamondType = DiamondType::Water;
    waterDiamond->gridX = 10;
    waterDiamond->gridY = gridHeight - 5;

    diamonds.push_back(waterDiamond);
    tiles[gridHeight - 5][10] = waterDiamond;

    //2
    MapTile* waterDiamond2 = new MapTile("water_diamond.png", 28 * TILE_SIZE, (gridHeight - 8) * TILE_SIZE, true, true
    );

    waterDiamond2->diamondType = DiamondType::Water;
    waterDiamond2->gridX = 28;
    waterDiamond2->gridY = gridHeight - 8;

    diamonds.push_back(waterDiamond2);
    tiles[gridHeight - 8][28] = waterDiamond2;

    //3
    MapTile* waterDiamond3 = new MapTile("water_diamond.png", 15 * TILE_SIZE, (gridHeight - 13) * TILE_SIZE, true, true
    );

    waterDiamond3->diamondType = DiamondType::Water;
    waterDiamond3->gridX = 15;
    waterDiamond3->gridY = gridHeight - 13;

    diamonds.push_back(waterDiamond3);
    tiles[gridHeight - 13][15] = waterDiamond3;

    //4
    MapTile* waterDiamond4 = new MapTile("water_diamond.png", 2 * TILE_SIZE, (gridHeight - 18) * TILE_SIZE, true, true
    );

    waterDiamond4->diamondType = DiamondType::Water;
    waterDiamond4->gridX = 2;
    waterDiamond4->gridY = gridHeight - 18;

    diamonds.push_back(waterDiamond4);
    tiles[gridHeight - 18][2] = waterDiamond4;
}

void Map::draw(sf::RenderWindow& window)
{
    for (auto& row : tiles)
        for (auto* tile : row)
            if (tile)
                window.draw(tile->sprite);
    for (auto* diamond : diamonds)
        if (diamond && !diamond->collected)
            window.draw(diamond->sprite);
}

std::vector<sf::FloatRect> Map::getColliders() const
{
    std::vector<sf::FloatRect> colliders;
    for (auto& row : tiles)
        for (auto* tile : row)
            if (tile && !tile->isPassable)
                colliders.push_back(tile->sprite.getGlobalBounds());

    return colliders;
}


std::vector<sf::FloatRect> Map::getHazardBounds() const
{
    std::vector<sf::FloatRect> bounds;
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridLength; x++)
        {
            MapTile* tile = hazards[y][x];
            if (tile && !tile->isPassable)
            {
                sf::FloatRect rect = tile->sprite.getGlobalBounds();
                rect.top -= TILE_SIZE * 0.5f;
                rect.height += TILE_SIZE * 0.5f;
                bounds.push_back(rect);
            }
        }
    }

    return bounds;
}

std::vector<MapTile*> Map::getHazardTiles() const
{
    std::vector<MapTile*> hazard;
    for (int y = 0; y < gridHeight; y++)
    {
        for (int x = 0; x < gridLength; x++)
        {
            MapTile* tile = hazards[y][x];
            if (tile && tile->hazardType != HazardType::None)
            {
                hazard.push_back(tile);
            }
        }
    }

    return hazard;
}


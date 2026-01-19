#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "mapTile.h"
#include <vector>
#include "Constants.h"

class Map {
private:
    void setUpTiles();

public:
    std::vector<std::vector<MapTile*>> tiles;
    int gridLength;
    int gridHeight;

    void setUpInitialState();
    Map();
    float getGroundY() const;

    void draw(sf::RenderWindow& window);
    std::vector<sf::FloatRect> getColliders() const;

    MapTile* fireDoor = nullptr;
    MapTile* waterDoor = nullptr;

    std::vector<std::vector<MapTile*>> hazards;
    std::vector<sf::FloatRect> getHazardBounds() const;

    std::vector<MapTile*> getHazardTiles() const;

    std::vector<MapTile*> diamonds;

    int totalDiamonds() const {
        return static_cast<int>(diamonds.size());
    }
};

#endif
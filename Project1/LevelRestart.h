#ifndef LEVEL_RESTART_H
#define LEVEL_RESTART_H

#include <SFML/System.hpp>
#include "Map.h"
#include "Character.h"

void restartLevel(
    Map& map,
    Character1& fire,
    Character2& water,
    sf::Clock& clock
);

#endif

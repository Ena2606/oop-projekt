#include "LevelRestart.h"
#include "Constants.h"

void restartLevel(
    Map& map,
    Character1& fire,
    Character2& water,
    sf::Clock& clock
) {
    
    map.setUpInitialState();

    
    fire.setPosition(50.f, (29 - 2) * TILE_SIZE - 50);
    water.setPosition(80.f, (29 - 2) * TILE_SIZE - 50);

    
    fire.stop();
    water.stop();
    fire.resetDying();
    water.resetDying();

    
    clock.restart();
}

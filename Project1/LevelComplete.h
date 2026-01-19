#ifndef LEVEL_COMPLETE_H
#define LEVEL_COMPLETE_H

#include <SFML/Graphics.hpp>

class LevelComplete
{
public:
    LevelComplete();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
};

#endif

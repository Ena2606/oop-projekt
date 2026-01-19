#include "LevelComplete.h"
#include <iostream>

LevelComplete::LevelComplete()
{
    if (!bgTexture.loadFromFile("LEVEL_COMPLETED.png"))
    {
        std::cerr << "Failed to load LEVEL_COMPLETED.png\n";
    }

    bgSprite.setTexture(bgTexture);

    float scaleX = 1275.f / bgTexture.getSize().x;
    float scaleY = 720.f / bgTexture.getSize().y;

    bgSprite.setScale(scaleX, scaleY);
    bgSprite.setPosition(0.f, 0.f);
}

void LevelComplete::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape)
    {
        window.close();
    }
}

void LevelComplete::draw(sf::RenderWindow& window)
{
    window.draw(bgSprite);
}

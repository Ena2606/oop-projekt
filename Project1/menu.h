#pragma once
#include <SFML/Graphics.hpp>

class Menu {
private:
    int selected;
    sf::Font font;
    sf::Text mainmenu[3];

public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int getSelected() const;
};
#pragma once

#include "Menu.h"
#include <string>

using namespace sf;
using namespace std;


Menu::Menu(float width, float height) {
    font.loadFromFile("Roboto-Regular.ttf");

    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color(180, 0, 0));
    mainmenu[0].setString("PLAY");
    mainmenu[0].setCharacterSize(40);
    mainmenu[0].setPosition(width / 2.2f, height / 4.f + 150);

    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color(250, 200, 80));
    mainmenu[1].setString("QUIT");
    mainmenu[1].setCharacterSize(35);
    mainmenu[1].setPosition(width / 2.2f, height / 4.f + 290);

    selected = 0;
}

void Menu::draw(RenderWindow& window) {
    for (int i = 0; i < 2; i++) {
        window.draw(mainmenu[i]);
    }
}

void Menu::MoveDown() {
    mainmenu[selected].setFillColor(Color(250, 200, 80));
    mainmenu[selected].setCharacterSize(35);

    selected = (selected + 1) % 2;

    mainmenu[selected].setFillColor(Color(180, 0, 0));
    mainmenu[selected].setCharacterSize(40);
}

void Menu::MoveUp() {
    mainmenu[selected].setFillColor(Color(250, 200, 80));
    mainmenu[selected].setCharacterSize(35);

    selected--;
    if (selected < 0)
        selected = 1;

    mainmenu[selected].setFillColor(Color(180, 0, 0));
    mainmenu[selected].setCharacterSize(40);
}

int Menu::getSelected() const {
    return selected;
}

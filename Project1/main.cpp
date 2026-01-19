#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "MapTile.h"
#include "Character.h"
#include "Menu.h"
#include "LevelComplete.h"
#include "LevelRestart.h"


using namespace sf;

enum class GameState {
    MENU,
    PLAYING,
    LEVEL_COMPLETE
};

int main()
{
    RenderWindow window(VideoMode(1275, 720), "Fireboy and Watergirl");
    window.setFramerateLimit(60);

    //////////////////////BG
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("castle_bg.jpg"))
    {
        return -1;
    }

    sf::Sprite bgSprite(bgTexture);


    float scaleX = static_cast<float>(window.getSize().x) / bgTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / bgTexture.getSize().y;


    bgSprite.setScale(scaleX, scaleY);
    bgSprite.setPosition(0.f, 0.f);

    ///////DIAMOND BROJAC

    sf::Texture emptyDiamondTex;
    emptyDiamondTex.loadFromFile("collected_diamond.png");

    ///////CRTANJE POSTAVKE DIJAMANTI i TEKST

    sf::Sprite diamondIcon(emptyDiamondTex);
    diamondIcon.setPosition(20.f, 20.f);
    diamondIcon.setScale(0.6f, 0.6f);
    sf::Font font;
    font.loadFromFile("Roboto-Regular.ttf");

    sf::Text diamondText;
    diamondText.setFont(font);
    diamondText.setCharacterSize(28);
    diamondText.setFillColor(sf::Color::White);
    diamondText.setPosition(60.f, 26.f);


    GameState gameState = GameState::MENU;

    Menu menu(1280.f, 720.f);

    Map map;

    Character1 fire("firegirl_spreadsheetreal.png");
    Character2 water("watergirlspreadsheetreal.png");

    fire.setPosition(50.f, 0.f);
    water.setPosition(80.f, 0.f);

    fire.setPosition(
        fire.getPosition().x,
        (29 - 2) * TILE_SIZE - 50
    );

    water.setPosition(
        water.getPosition().x,
        (29 - 2) * TILE_SIZE - 50
    );


    Clock clock;

    LevelComplete levelComplete;

    bool levelRestarting = false;
    float dyingTimer = 0.f;
    int collectedDiamonds = 0;


    ////////////MAIN GAME LOOP
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (gameState == GameState::MENU && event.type == Event::KeyPressed)
            {
        

                if (event.key.code == Keyboard::Up)
                    menu.MoveUp();

                if (event.key.code == Keyboard::Down)
                    menu.MoveDown();

                if (event.key.code == Keyboard::Enter)
                {
                    if (menu.getSelected() == 0)
                    {
                        gameState = GameState::PLAYING;
                        clock.restart();
                    }
                    else
                        window.close();
                }
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                if (gameState == GameState::PLAYING)
                    gameState = GameState::MENU;
                else
                    window.close();
            }
        }

        window.clear();

        window.draw(bgSprite);

        ///////////////MENU
        if (gameState == GameState::MENU)
        {
            menu.draw(window);
        }

        ///////////////PLAYING
        else if (gameState == GameState::PLAYING)
        {   
            

            float dt = clock.restart().asSeconds();

            ////////////////FIRE KEYS
            bool fireMoving = false;

            
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                fire.moveLeft();
                fireMoving = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                fire.moveRight();
                fireMoving = true;
            }
            if (!fireMoving)
                fire.stop();

            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                if (Keyboard::isKeyPressed(Keyboard::A))
                    fire.jumpLeft();
                else if (Keyboard::isKeyPressed(Keyboard::D))
                    fire.jumpRight();
                fire.jump();
            }
            if (Keyboard::isKeyPressed(Keyboard::R)) {
                collectedDiamonds = 0;
                restartLevel(map, fire, water, clock);
                
            }

            if (Keyboard::isKeyPressed(Keyboard::E))
                fire.backflip();

            

            ////////////////WATER KEYS
            bool waterMoving = false;

            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                water.moveLeft();
                waterMoving = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                water.moveRight();
                waterMoving = true;
            }
            if (!waterMoving)
                water.stop();

            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (Keyboard::isKeyPressed(Keyboard::Left))
                    water.jumpLeft();
                else if (Keyboard::isKeyPressed(Keyboard::Right))
                    water.jumpRight();
                water.jump();
            }

            
            /////UPDATE
            fire.update(dt);
            water.update(dt);


            fire.resolveCollisions(map.getColliders(), dt);
            water.resolveCollisions(map.getColliders(), dt);

            ///////HAZARDI

            auto hazardTiles = map.getHazardTiles();

            for (auto* tile : hazardTiles)
            {
                sf::FloatRect bounds = tile->sprite.getGlobalBounds();

                
                if (tile->hazardType == HazardType::Spikes ||
                    tile->hazardType == HazardType::WaterFloor ||
                    tile->hazardType == HazardType::FireFloor)
                {
                    bounds.top -= TILE_SIZE * 0.5f;
                    bounds.height += TILE_SIZE * 0.5f;
                    bounds.width -= TILE_SIZE *0.4f;
                    bounds.left += TILE_SIZE * 0.f;
                }


                if (!levelRestarting)
                {
                    switch (tile->hazardType)
                    {
                    case HazardType::Spikes:
                        if (fire.getBounds().intersects(bounds) ||
                            water.getBounds().intersects(bounds))
                        {
                            fire.dying();
                            water.dying();
                            collectedDiamonds = 0;
                            levelRestarting = true;
                            dyingTimer = 0.f;
                            break;
                        }
                        break;
                    case HazardType::WaterFloor:
                        if (fire.getBounds().intersects(bounds))
                        {
                            fire.dying();
                            collectedDiamonds = 0;
                            levelRestarting = true;
                            dyingTimer = 0.f;

                            break;
                        }
                        break;
                    case HazardType::FireFloor:
                        if (water.getBounds().intersects(bounds))
                        {
                            water.dying();
                            collectedDiamonds = 0;
                            levelRestarting = true;
                            dyingTimer = 0.f;
                            break;
                        }
                        break;
                    default: 
                        break;
                    }
                }
            }

            ////////////loop za restart//////////
            if (levelRestarting)
            {
                dyingTimer += dt;

                fire.stop();
                water.stop();

                fire.update(dt);
                water.update(dt);

                if (dyingTimer >= 1.f)
                {   
                    collectedDiamonds = 0;
                    restartLevel(map, fire, water, clock);
                    levelRestarting = false;
                }
            }
          

            /////////////////SKUPLJANJE DIJAMANATA

            for (auto* diamond : map.diamonds)
            {
                if (!diamond || diamond->collected)
                    continue;

                sf::FloatRect diamondBounds = diamond->sprite.getGlobalBounds();

                
                diamondBounds.left += TILE_SIZE * 0.2f;
                diamondBounds.width -= TILE_SIZE * 0.4f;
                diamondBounds.top += TILE_SIZE * 0.2f;
                diamondBounds.height -= TILE_SIZE * 0.4f;

                
                
                if (diamond->diamondType == DiamondType::Fire &&
                    fire.getBounds().intersects(diamondBounds))
                {
                    diamond->collected = true;
                    map.tiles[diamond->gridY][diamond->gridX] = nullptr;
                }
                
                else if (diamond->diamondType == DiamondType::Water &&
                    water.getBounds().intersects(diamondBounds))
                {
                    diamond->collected = true;
                    map.tiles[diamond->gridY][diamond->gridX] = nullptr;
                }
            }

            //BROJAC DIAMOND UPDATE COUNTER//////////////////7
            collectedDiamonds = 0;
            for (auto* diamond : map.diamonds)
            {
                if (diamond && diamond->collected)
                    collectedDiamonds++;
            }




            ////////////BROJAC DIAMOND UPDATE TEKST

            diamondText.setString(std::to_string(collectedDiamonds));


            /////////////////////DOORS       
            bool fireOnDoor = fire.getBounds().intersects(map.fireDoor->sprite.getGlobalBounds());
            bool waterOnDoor = water.getBounds().intersects(map.waterDoor->sprite.getGlobalBounds());

            bool allDiamondsCollected = true;
            for (auto* diamond : map.diamonds)
            {
                if (diamond && !diamond->collected)
                {
                    allDiamondsCollected = false;
                    break;
                }
            }

            if (fireOnDoor && waterOnDoor && allDiamondsCollected)
            {
                gameState = GameState::LEVEL_COMPLETE;
            }



        }

        ///////////////////////DRAW
        window.clear();

        if (gameState == GameState::MENU)
        {
            menu.draw(window);
        }
        else if (gameState == GameState::PLAYING)
        {

            window.draw(bgSprite);
            map.draw(window);
            fire.draw(window);
            water.draw(window);
            window.draw(diamondIcon);
            window.draw(diamondText);

        }
        else if (gameState == GameState::LEVEL_COMPLETE)
        {
            levelComplete.draw(window);
        }

        window.display();

    }
    return 0;
}
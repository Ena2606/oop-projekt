#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <vector>

enum class CharacterType {
    FireGirl,
    WaterGirl
};

enum class AnimationState
{
    Idle,
    MovingL,
    MovingR,
    JumpL,
    JumpR,
    Dying,
    Backflip
};
class Character1
{
public:
    Character1(const std::string& texturePath);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    void moveLeft();
    void moveRight();
    void jump();
    void jumpLeft();
    void jumpRight();
    void stop();
    void dying();
    void backflip();
    bool dyingFlag = false;

    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;

    void applyGravity(float dt);
    void resolveCollisions(const std::vector<sf::FloatRect>& colliders, float dt);

    CharacterType getType() const { return CharacterType::FireGirl; }

    sf::Vector2f getPosition() const;
    bool isDying() const { return dyingFlag; }
    void resetDying() { dyingFlag = false; }

private:
    void loadAnimations();
    void updateAnimation(float dt);
    void setState(AnimationState state);
    void updateDirection();

    sf::Texture texture;
    sf::Sprite sprite;

    std::vector<sf::IntRect> idleFrames;
    std::vector<sf::IntRect> moveLFrames;
    std::vector<sf::IntRect> moveRFrames;
    std::vector<sf::IntRect> jumpLFrames;
    std::vector<sf::IntRect> jumpRFrames;
    std::vector<sf::IntRect> dyingFrames;
    std::vector<sf::IntRect> backflipFrames;

    AnimationState currentState;

    float frameTime;
    float elapsedTime;
    std::size_t currentFrame;

    sf::Vector2f velocity;
    bool onGround;
    bool facingRight;

};

class Character2
{
public:
    Character2(const std::string& texturePath);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    void moveLeft();
    void moveRight();
    void jump();
    void jumpLeft();
    void jumpRight();
    void dying();
    void stop();
    bool dyingFlag = false;


    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;

    sf::Vector2f getPosition() const;

    void applyGravity(float dt);
    void resolveCollisions(const std::vector<sf::FloatRect>& colliders, float dt);

    CharacterType getType() const { return CharacterType::WaterGirl; }
    bool isDying() const { return dyingFlag; }
    void resetDying() { dyingFlag = false; }

private:
    void loadAnimations();
    void updateAnimation(float dt);
    void setState(AnimationState state);
    void updateDirection();

    sf::Texture texture;
    sf::Sprite sprite;

    std::vector<sf::IntRect> idleFrames;
    std::vector<sf::IntRect> moveLFrames;
    std::vector<sf::IntRect> moveRFrames;
    std::vector<sf::IntRect> jumpLFrames;
    std::vector<sf::IntRect> jumpRFrames;
    std::vector<sf::IntRect> dyingFrames;

    AnimationState currentState;

    float frameTime;
    float elapsedTime;
    std::size_t currentFrame;

    sf::Vector2f velocity;
    bool onGround;
    bool facingRight;
};

#endif